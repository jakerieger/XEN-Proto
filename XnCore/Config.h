// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Types.h"

#define MINI_CASE_SENSITIVE
#include <ini.h>

enum class EWindowMode {
    Windowed,
    Borderless,
    Fullscreen,
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

struct FInputMap {
    Dictionary<str, str> InputMappings;

    [[nodiscard]] str GetInputMapping(const str& name) const;
    void AddInputMapping(const str& name, const str& value);
};

class Config {
public:
    Config() = default;

    void LoadRenderingConfig(const Path& config);
    void LoadAudioConfig(const Path& config);
    void LoadInputMappings(const Path& config);

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

    [[nodiscard]] FInputMap GetInputMap() const {
        return mInputMap;
    }

private:
    FRenderingConfig mRenderingConfig;
    FAudioConfig mAudioConfig;
    FInputMap mInputMap;
};
