// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once
#include "Shared/Types.h"

struct FKeyEvent {
    int KeyCode;
};

struct FMouseButtonEvent {
    int Button;
};

struct FMouseMoveEvent {
    f64 X;
    f64 Y;
};

struct FMouseWheelEvent {
    f64 Delta;
};