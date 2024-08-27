// Author: Jake Rieger
// Created: 8/26/2024.
//

#include "AudioContext.h"
#include "AudioUtils.h"
#include "Events.h"

#include <iostream>
#include <AL/al.h>
#include <AL/alext.h>
#include <AudioFile.h>

AudioContext::AudioContext(const Weak<Config>& config,
                           const Shared<EventDispatcher>& eventDispatcher) {
    mConfig          = config;
    mEventDispatcher = eventDispatcher;

    const auto deviceName = alcGetString(None, ALC_DEFAULT_DEVICE_SPECIFIER);
    mDevice               = alcOpenDevice(deviceName);
    if (!mDevice) {
        throw RuntimeError("alcOpenDevice() failed");
    }
    mContext = alcCreateContext(mDevice, None);
    mCurrent = alcMakeContextCurrent(mContext);
    if (!mCurrent) {
        throw RuntimeError("alcMakeContextCurrent() failed");
    }
    if (!CheckALCErrors()) {
        throw RuntimeError("alcMakeContextCurrent() failed");
    }
    CheckALErrors();

    mEventDispatcher->RegisterListener<PlaySoundEvent>([this](const PlaySoundEvent& event) {
        PlaySound(event.Name, event.FilePath, event.Gain, event.Loop);
    });
}

AudioContext::~AudioContext() {
    for (auto& [source, buffer, _] : mChannels) {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
    }
    mChannels.clear();

    mContext = alcGetCurrentContext();
    mDevice  = alcGetContextsDevice(mContext);
    alcMakeContextCurrent(None);
    alcDestroyContext(mContext);
    alcCloseDevice(mDevice);
}

void AudioContext::PlaySound(const str& name, const Path& file, f32 gain, bool isLoop) {
    if (file.empty()) {
        return;
    }

    AudioFile<f32> sound;
    sound.shouldLogErrorsToConsole(true);
    if (!sound.load(file.string())) {
        throw RuntimeError("Failed to load sound file");
    }

    ALenum format;
    if (sound.isMono()) {
        format = AL_FORMAT_MONO_FLOAT32;
    } else {
        format = AL_FORMAT_STEREO_FLOAT32;
    }

    u32 alSource;
    u32 alSampleSet;
    Vector<f32> samples;
    samples.reserve(sound.getNumSamplesPerChannel() * sound.getNumChannels());

    if (sound.isMono()) {
        samples = sound.samples.at(0);
    } else {
        samples = Interleave(sound.samples.at(0), sound.samples.at(1));
    }

    // OpenAL requires that the number of samples be a multiple of the data type size in bytes
    // (float in this case) * the number of channels. If it's not, this line adds additional
    // silence at the end of the buffer to make it a multiple.
    samples.resize(
      MakeMultiple(CAST<i32>(samples.size()), CAST<i32>(sizeof(f32)) * sound.getNumChannels()),
      0.f);

    Normalize(samples, kTargetPeak);

    const auto masterVolume = mConfig.lock()->GetAudioConfig().MasterVolume;
    const auto finalVolume  = gain * masterVolume;
    // TODO: Handle audio tags to determine which volume category to use

    alGenSources(1, &alSource);
    alGenBuffers(1, &alSampleSet);
    alBufferData(alSampleSet,
                 format,
                 samples.data(),
                 CAST<ALsizei>(samples.size()),
                 CAST<ALsizei>(sound.getSampleRate()));
    alSourcei(alSource, AL_BUFFER, CAST<ALint>(alSampleSet));
    alSourcei(alSource, AL_LOOPING, isLoop);
    alSourcef(alSource, AL_GAIN, finalVolume);

    sound.samples.clear();

    alSourcePlay(alSource);
    mChannels.emplace_back(alSource, alSampleSet, name);
}

bool AudioContext::CheckALErrors() {
    if (const ALenum error = alGetError(); error != AL_NO_ERROR) {
        switch (error) {
            case AL_INVALID_NAME:
                std::cout << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function"
                          << std::endl;
                break;
            case AL_INVALID_ENUM:
                std::cout
                  << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function"
                  << std::endl;
                break;
            case AL_INVALID_VALUE:
                std::cout << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function"
                          << std::endl;
                break;
            case AL_INVALID_OPERATION:
                std::cout << "AL_INVALID_OPERATION: the requested operation is not valid"
                          << std::endl;
                break;
            case AL_OUT_OF_MEMORY:
                std::cout << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL "
                             "running out of memory"
                          << std::endl;
                break;
            default:
                std::cout << "UNKNOWN AL ERROR: " << error << std::endl;
        }
        return false;
    }
    return true;
}

bool AudioContext::CheckALCErrors() const {
    if (const ALCenum error = alcGetError(mDevice); error != ALC_NO_ERROR) {
        switch (error) {
            case ALC_INVALID_VALUE:
                std::cout << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function"
                          << std::endl;
                break;
            case ALC_INVALID_DEVICE:
                std::cout << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function"
                          << std::endl;
                break;
            case ALC_INVALID_CONTEXT:
                std::cout << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function"
                          << std::endl;
                break;
            case ALC_INVALID_ENUM:
                std::cout
                  << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function"
                  << std::endl;
                break;
            case ALC_OUT_OF_MEMORY:
                std::cout << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL "
                             "function"
                          << std::endl;
                break;
            default:
                std::cout << "UNKNOWN ALC ERROR: " << error << std::endl;
        }
        return false;
    }
    return true;
}