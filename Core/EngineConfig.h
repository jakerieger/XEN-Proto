// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"

#include <ini.h>

enum class EWindowMode {
    Windowed,
    Borderless,
    Fullscreen,
};

struct alignas(4) FInternalConfig {
    f32 FixedTimestep   = 60.f;
    f32 PhysicsTimestep = 120.f;
};

struct alignas(4) FRenderingConfig {
    u32 ResX               = 1280;
    u32 ResY               = 720;
    bool VSync             = false;
    EWindowMode WindowMode = EWindowMode::Windowed;
};

struct alignas(4) FAudioConfig {
    f32 MasterVolume = 1.f;
    f32 FxVolume     = 1.f;
    f32 MusicVolume  = 1.f;
    f32 VoiceVolume  = 1.f;
};

class EngineConfig {
public:
    EngineConfig() = default;
    void LoadConfig(const Path& config);

    [[nodiscard]] FInternalConfig GetInternalConfig() const {
        return mInternalConfig;
    }

    void SetInternalConfig(const FInternalConfig& config) {
        mInternalConfig = config;
    }

    [[nodiscard]] FRenderingConfig GetRenderingConfig() const {
        return mRenderingConfig;
    }

    void SetRenderingConfig(const FRenderingConfig& renderingConfig) {
        mRenderingConfig = renderingConfig;
    }

    [[nodiscard]] FAudioConfig GetAudioConfig() const {
        return mAudioConfig;
    }

    void SetAudioConfig(const FAudioConfig& audioConfig) {
        mAudioConfig = audioConfig;
    }

private:
    FInternalConfig mInternalConfig;
    FRenderingConfig mRenderingConfig;
    FAudioConfig mAudioConfig;

    void LoadInternalConfig(mINI::INIStructure& config);
    void LoadRenderingConfig(mINI::INIStructure& config);
    void LoadAudioConfig(mINI::INIStructure& config);
};
