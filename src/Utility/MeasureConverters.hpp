// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <numbers>

namespace MeasureConverters {
    constexpr double degToRad(double angle) {
        return angle / 180.0 * std::numbers::pi;
    }

    constexpr double mmToM(double length) {
        return length * 1.0e-3;
    }

    constexpr double mm3ToM3(double volume) {
        return volume * 1.0e-9;
    }

    constexpr double gToKg(double mass) {
        return mass * 1.0e-3;
    }

    constexpr double torrCmToPaM(double townsend) {
        return townsend * 100 / 133.332;
    }
}
