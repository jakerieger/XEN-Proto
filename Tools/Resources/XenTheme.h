#pragma once

#include "Shared/Types.h"

#include <imgui.h>

static ImVec4 HexToRGBA(const u32 hex) {
    const unsigned char alphaByte = (hex >> 24) & 0xFF;
    const unsigned char redByte   = (hex >> 16) & 0xFF;
    const unsigned char greenByte = (hex >> 8) & 0xFF;
    const unsigned char blueByte  = hex & 0xFF;

    auto a = static_cast<float>(static_cast<u32>(alphaByte) / 255.0);
    auto r = static_cast<float>(static_cast<u32>(redByte) / 255.0);
    auto g = static_cast<float>(static_cast<u32>(greenByte) / 255.0);
    auto b = static_cast<float>(static_cast<u32>(blueByte) / 255.0);

    return {r, g, b, a};
}

static Dictionary<std::string, ImVec4> kXenTheme = {{"panel", HexToRGBA(0xFF161722)},
                                                    {"scene", HexToRGBA(0xFFFFFFFF)},
                                                    {"frame", HexToRGBA(0xFF1a1c29)},
                                                    {"accent", HexToRGBA(0xFF4680fa)},
                                                    {"border", HexToRGBA(0xFF0A0B10)},
                                                    {"text", HexToRGBA(0xFFc0caf5)},
                                                    {"text_inactive", HexToRGBA(0xFF414868)},
                                                    {"button", HexToRGBA(0xFF4680fa)},
                                                    {"button_hover", HexToRGBA(0xF04680fa)},
                                                    {"selected", HexToRGBA(0xFF101118)},
                                                    {"header", HexToRGBA(0xFF1a1b26)},
                                                    {"menu", HexToRGBA(0xFF0A0B10)},
                                                    {"success", HexToRGBA(0xFF73daca)},
                                                    {"warning", HexToRGBA(0xFFff9e64)},
                                                    {"error", HexToRGBA(0xFFFF3366)},
                                                    {"separator", HexToRGBA(0xFF24283b)}};