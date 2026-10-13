// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Battery.hpp"

Battery::Battery(
    double resistance
):
    resistance_(resistance) {}

void Battery::step(double /*dt*/) {}
