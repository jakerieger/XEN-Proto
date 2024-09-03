// Author: Jake Rieger
// Created: 9/3/2024.
//

#pragma once

#include "Shared/Types.h"

namespace FileTemplates {
    inline str
    GameObjectSourceFile(const str& className, bool drawable, bool inputListener, bool physicsObj) {
        auto header = R""(#pragma once

#include "XnCore/GameObject.h"
)"";

        return header;
    }
}  // namespace FileTemplates