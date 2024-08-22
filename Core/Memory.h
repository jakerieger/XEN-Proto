// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <cstdlib>
// #include <execinfo.h>
// #include <cxxabi.h>
#include <mutex>

std::unordered_map<void*, size_t> gAllocationRegistry;
std::mutex gAllocationMutex;

void* operator new(size_t size) {}