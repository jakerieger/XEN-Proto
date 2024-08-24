// Author: Jake Rieger
// Created: 8/24/2024.
//

#pragma once

#include <type_traits>

template<typename Base, typename Derived>
concept IsBaseOf = std::is_base_of_v<Base, Derived>;