// SPDX-License-Identifier: AGPL-3.0-or-later
#include "SparkPlug.hpp"
#include "Constants/GasConstants.hpp"
#include "Engine/GasDynamics/Cylinder/Cylinder.hpp"
#include <cmath>

namespace GC = GasConstants;

SparkPlug::SparkPlug(
    double gap,
    double resistor
):
    gap_(gap),
    resistor_(resistor),
    cylinder_(nullptr),
    isArcing_(false) {}

double SparkPlug::getUBreak() const {
    double N = cylinder_->getPressure() / (GC::kB * cylinder_->getTemperature());
    double delta = N / GC::N0;
    double dEffective = gap_ * delta;

    return GC::PASHEN_K1 * (dEffective) + GC::PASHEN_K2 * std::sqrt(dEffective); //Инженерный Пашен
}



