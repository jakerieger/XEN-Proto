// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Config.h"
#include "InputMap.h"

#include <iostream>

str FInputMap::GetInputMapping(const str& name) const {
    return InputMappings.find(name)->second;
}

void FInputMap::AddInputMapping(const str& name, const str& value) {
    InputMappings[name] = value;
}

void Config::LoadRenderingConfig(const Path& config) {
    const auto filename = mDataPath / config;
    const mINI::INIFile configIni(filename.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        std::cout << "Failed to read config file: " << config << std::endl;
        return;
    }

    mRenderingConfig.ResX  = std::stoi(ini["Rendering"]["ResX"]);
    mRenderingConfig.ResY  = std::stoi(ini["Rendering"]["ResY"]);
    mRenderingConfig.VSync = (ini["Rendering"]["VSync"] == "on");

    const auto windowMode = ini["Rendering"]["WindowMode"];
    if (windowMode == "windowed") {
        mRenderingConfig.WindowMode = EWindowMode::Windowed;
    } else if (windowMode == "borderless") {
        mRenderingConfig.WindowMode = EWindowMode::Borderless;
    } else if (windowMode == "fullscreen") {
        mRenderingConfig.WindowMode = EWindowMode::Fullscreen;
    }
}

void Config::LoadAudioConfig(const Path& config) {
    const auto filename = mDataPath / config;
    const mINI::INIFile configIni(filename.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        std::cout << "Failed to read config file: " << config << std::endl;
        return;
    }

    mAudioConfig.MasterVolume = std::stof(ini["Audio"]["MasterVolume"]);
    mAudioConfig.FxVolume     = std::stof(ini["Audio"]["FxVolume"]);
    mAudioConfig.MusicVolume  = std::stof(ini["Audio"]["MusicVolume"]);
    mAudioConfig.VoiceVolume  = std::stof(ini["Audio"]["VoiceVolume"]);
}

void Config::LoadInputMappings(const Path& config) {
    const auto filename = mDataPath / config;
    const mINI::INIFile configIni(filename.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        std::cout << "Failed to read config file: " << config << std::endl;
        return;
    }

    auto it = ini["InputMap"].begin();
    while (it != ini["InputMap"].end()) {
        mInputMap.InputMappings[it->first] = it->second;
        ++it;
    }
}