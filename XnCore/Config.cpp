// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Config.h"
#include "InputMap.h"

void Config::LoadConfig(const Path& config) {
    if (!FileSystem::exists(config)) {
        throw RuntimeError("Config not found");
    }

    const mINI::INIFile configIni(config.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        throw RuntimeError("Unable to read config file");
    }

    LoadRenderingConfig(ini);
    LoadAudioConfig(ini);
    LoadInputMappings(ini);
}

str FInputMap::GetInputMapping(const str& name) const {
    return InputMappings.find(name)->second;
}

void FInputMap::AddInputMapping(const str& name, const str& value) {
    InputMappings[name] = value;
}

void Config::LoadRenderingConfig(mINI::INIStructure& config) {
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

void Config::LoadAudioConfig(mINI::INIStructure& config) {
    mAudioConfig.MasterVolume = std::stof(config["Game.Audio"]["MasterVolume"]);
    mAudioConfig.FxVolume     = std::stof(config["Game.Audio"]["FxVolume"]);
    mAudioConfig.MusicVolume  = std::stof(config["Game.Audio"]["MusicVolume"]);
    mAudioConfig.VoiceVolume  = std::stof(config["Game.Audio"]["VoiceVolume"]);
}

void Config::LoadInputMappings(mINI::INIStructure& config) {
    auto it = config["Game.Input"].begin();
    while (it != config["Game.Input"].end()) {
        mInputMap.InputMappings[it->first] = it->second;
        ++it;
    }
}