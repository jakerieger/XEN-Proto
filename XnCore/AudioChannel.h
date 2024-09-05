// Author: Jake Rieger
// Created: 8/27/2024.
//

#pragma once

#include "Shared/Types.h"

struct FAudioChannel {
    FAudioChannel();
    FAudioChannel(u32 src, u32 buf, const str& name) : Source(src), Buffer(buf), Name(name) {}
    u32 Source = 0;
    u32 Buffer = 0;
    str Name;
};