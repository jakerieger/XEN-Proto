// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "EngineConfig.h"
#include "Shared/IO.h"
#include "Shared/ini.h"

void EngineConfig::LoadConfig(const Path& config) {
    if (!FileSystem::exists(config)) {
        throw RuntimeError("Config not found");
    }

    const mINI::INIFile configIni(config.string());
    mINI::INIStructure ini;
    if (!configIni.read(ini)) {
        throw RuntimeError("Unable to read config file");
    }

    mRenderingConfig.Width  = std::stoi(ini["Engine.Rendering"]["ResX"]);
    mRenderingConfig.Height = std::stoi(ini["Engine.Rendering"]["ResY"]);
    mRenderingConfig.VSync  = (ini["Engine.Rendering"]["VSync"] == "on");
}