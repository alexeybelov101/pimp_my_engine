// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Camlobe.hpp"
#include <numbers>
#include <cmath>

Camlobe::Camlobe(double maxLift, double duration):
    maxLift_(maxLift), duration_(duration) {}

double Camlobe::getLift(double angle) const {
    if (angle < 0 || angle > duration_) return 0.0;

    double phase = (angle / duration_) * std::numbers::pi;

    return maxLift_ * std::sin(phase);
}
