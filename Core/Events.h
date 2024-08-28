// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include <utility>

#include "EventSystem.h"

static constexpr int kResolutionChangedEventId = 0x01;
static constexpr int kPlaySoundEventId         = 0x02;

class ResolutionChangedEvent final : public IEvent {
public:
    ResolutionChangedEvent(int width, int height)
        : IEvent(kResolutionChangedEventId), Width(width), Height(height) {}
    int Width;
    int Height;
};

class PlaySoundEvent final : public IEvent {
public:
    PlaySoundEvent(str name, Path path, f32 gain = 0.5f, bool loop = false)
        : IEvent(kPlaySoundEventId), Loop(loop), Name(std::move(name)), FilePath(std::move(path)),
          Gain(gain) {}
    bool Loop;
    str Name;
    Path FilePath;
    f32 Gain;
};