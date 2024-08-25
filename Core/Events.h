// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include "EventSystem.h"

static constexpr int kResolutionChangedEventId = 0x01;

class ResolutionChangedEvent final : public IEvent {
public:
    ResolutionChangedEvent(int width, int height)
        : IEvent(kResolutionChangedEventId), Width(width), Height(height) {}
    int Width;
    int Height;
};