// SPDX-License-Identifier: AGPL-3.0-or-later
#include "SparkPlug.hpp"
#include "Engine/GasDynamics/Cylinder/Cylinder.hpp"

SparkPlug::SparkPlug(
    double gap,
    double resistor
):
    gap_(gap),
    resistor_(resistor),
    cylinder_(nullptr) {}


