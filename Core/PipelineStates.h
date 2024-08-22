// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

class PipelineStates {
public:
    PipelineStates() = default;
    static void SetDefaults();
    static void DrawSolid();
    static void DrawWire();
};
