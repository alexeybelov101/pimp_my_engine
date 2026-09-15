// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Atmosphere.hpp"
#include "Constants/GasDynamics.hpp"
#include <limits>

namespace GD = GasDynamics;

Atmosphere::Atmosphere():
    leftBoundary_(AtmosphereBoundary(this, true)),
    rightBoundary_(AtmosphereBoundary(this, false)),
    cell_(
        GD::RHO_AMBIENT,
        0.0,
        GD::P_ATM / (GD::GAMMA - 1.0)
    ) {}

const IBoundary& Atmosphere::getBoundary(bool isLeft) const {
    return isLeft ? leftBoundary_ : rightBoundary_;
}

void Atmosphere::step(double /*dt*/) {};

// AtmosphereBoundary
//==============================================================================
Atmosphere::AtmosphereBoundary::AtmosphereBoundary(Atmosphere* owner, bool isLeft)
    : owner_(owner), isLeft_(isLeft) {}

Cell Atmosphere::AtmosphereBoundary::getState() const {
    return owner_->cell_;
}

void Atmosphere::AtmosphereBoundary::setFlux(const Flux& /*flux*/) const {
    // Атмосфера — бесконечный резервуар, поток в неё не меняет её состояние
}

double Atmosphere::AtmosphereBoundary::getArea() const {
    return std::numeric_limits<double>::infinity();
}

double Atmosphere::AtmosphereBoundary::getAperture() const {
    return std::numeric_limits<double>::infinity();
}

bool Atmosphere::AtmosphereBoundary::isLeft() const {
    return isLeft_;
}
