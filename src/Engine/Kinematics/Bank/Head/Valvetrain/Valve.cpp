// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Valve.hpp"
#include <numbers>

Valve::Valve(
    double headRadius,
    double sinSeatA,
    double cosSeatA
):
    headRadius_(headRadius),
    sinSeatA_(sinSeatA),
    cosSeatA_(cosSeatA) {}

double Valve::getFlowArea(double lift) const {
    return std::numbers::pi * lift * cosSeatA_ * (headRadius_ * 2.0 - lift * sinSeatA_ * cosSeatA_);
}

double Valve::getValveArea() const {
    return std::numbers::pi * headRadius_ * headRadius_;
}
