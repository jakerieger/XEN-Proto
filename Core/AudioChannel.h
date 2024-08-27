// Author: Jake Rieger
// Created: 8/27/2024.
//

#pragma once

#include "Shared/Types.h"

struct FAudioChannel {
    u32 Source = 0;
    u32 Buffer = 0;
    str Name;
};