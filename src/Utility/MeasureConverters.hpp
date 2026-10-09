// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <numbers>

namespace MeasureConverters {
    inline double degToRad(double angle) {
        return angle / 180.0 * std::numbers::pi;
    }

    inline double mmToM(double length) {
        return length * 1.0e-3;
    }

    inline double mm3ToM3(double volume) {
        return volume * 1.0e-9;
    }

    inline double gToKg(double mass) {
        return mass * 1.0e-3;
    }
}
