// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Math.h"

#if defined(_MSC_VER)
    #include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
    #include <cpuid.h>
#endif

namespace XnMath {
    void Cpuid(int cpuInfo[4], int funcId) {
#if defined(_MSC_VER)
        __cpuid(cpuInfo, funcId);
#elif defined(__GNUC__) || defined(__clang__)
        __cpuid(funcId, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
#endif
    }

    bool AvxSupported() {
        int cpuInfo[4];
        Cpuid(cpuInfo, 1);

        const bool osAvxSupported = (cpuInfo[2] & (1 << 27)) != 0;  // Check OS support for AVX
        const bool avxSupport     = (cpuInfo[2] & (1 << 28)) != 0;  // Check AVX feature flag

        return osAvxSupported && avxSupport;
    }

    bool SseSupported() {
        int cpuInfo[4];
        Cpuid(cpuInfo, 1);

        return (cpuInfo[3] & (1 << 25)) != 0;
    }

    bool VerifySupport() {
        return SseSupported() && AvxSupported();
    }

    f32 ToDegrees(f32 angle) {
        return angle * (180.f / kPi);
    }

    f32 ToRadians(f32 angle) {
        return angle * (kPi / 180.f);
    }
}  // namespace XnMath