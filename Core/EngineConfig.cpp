// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "EngineConfig.h"

void EngineConfig::LoadConfig(const Path& config) {
    if (!FileSystem::exists(config)) {
        throw RuntimeError("Config not found");
    }

    const mINI::INIFile configIni(config.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        throw RuntimeError("Unable to read config file");
    }

    LoadInternalConfig(ini);
    LoadRenderingConfig(ini);
    LoadAudioConfig(ini);
}

void EngineConfig::LoadInternalConfig(mINI::INIStructure& config) {
    mInternalConfig.FixedTimestep   = std::stof(config["Engine.Internal"]["FixedTimestep"]);
    mInternalConfig.PhysicsTimestep = std::stof(config["Engine.Internal"]["PhysicsTimestep"]);
}

void EngineConfig::LoadRenderingConfig(mINI::INIStructure& config) {
    mRenderingConfig.ResX  = std::stoi(config["Engine.Rendering"]["ResX"]);
    mRenderingConfig.ResY  = std::stoi(config["Engine.Rendering"]["ResY"]);
    mRenderingConfig.VSync = (config["Engine.Rendering"]["VSync"] == "on");

    const auto windowMode = config["Engine.Rendering"]["WindowMode"];
    if (windowMode == "windowed") {
        mRenderingConfig.WindowMode = EWindowMode::Windowed;
    } else if (windowMode == "borderless") {
        mRenderingConfig.WindowMode = EWindowMode::Borderless;
    } else if (windowMode == "fullscreen") {
        mRenderingConfig.WindowMode = EWindowMode::Fullscreen;
    }
}

void EngineConfig::LoadAudioConfig(mINI::INIStructure& config) {
    mAudioConfig.MasterVolume = std::stof(config["Engine.Audio"]["MasterVolume"]);
    mAudioConfig.FxVolume     = std::stof(config["Engine.Audio"]["FxVolume"]);
    mAudioConfig.MusicVolume  = std::stof(config["Engine.Audio"]["MusicVolume"]);
    mAudioConfig.VoiceVolume  = std::stof(config["Engine.Audio"]["VoiceVolume"]);
}