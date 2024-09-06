// Author: Jake Rieger
// Created: 8/26/2024.
//

#pragma once

#include "Types.h"
#include "AudioChannel.h"
#include "Config.h"
#include "EventSystem.h"

#include <AL/alc.h>

class AudioContext {
public:
    AudioContext(const Weak<Config>& config, const Shared<EventDispatcher>& eventDispatcher);
    ~AudioContext();

private:
    ALCdevice* mDevice   = None;
    ALCcontext* mContext = None;
    ALCboolean mCurrent  = false;
    Vector<FAudioChannel> mChannels;

    static bool CheckALErrors();
    [[nodiscard]] bool CheckALCErrors() const;

    Weak<Config> mConfig;
    Shared<EventDispatcher> mEventDispatcher;

    void PlaySound(const str& name, const Path& file, f32 gain = 0.5f, bool isLoop = false);

    /// Amplitude target for normalization
    static constexpr f32 kTargetPeak = 0.99f;
};
