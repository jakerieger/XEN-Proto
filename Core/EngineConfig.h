// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"

struct RenderingConfig {
    u32 Width;
    u32 Height;
    bool VSync;
};

class EngineConfig {
public:
    EngineConfig() = default;
    void LoadConfig(const Path& config);

    [[nodiscard]] RenderingConfig GetRenderingConfig() const {
        return mRenderingConfig;
    }

private:
    RenderingConfig mRenderingConfig;
};
