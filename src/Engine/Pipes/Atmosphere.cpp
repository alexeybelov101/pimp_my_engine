#include "Atmosphere.hpp"
#include "../../Constants/GasDynamics.hpp"
#include <limits>

namespace GD = GasDynamics;

Atmosphere::Atmosphere():
    boundary_(this),
    cell_(
        GD::RHO_AMBIENT,
        0.0,
        GD::P_ATM / (GD::GAMMA - 1.0)
    ) {}

const IBoundary& Atmosphere::getLeftBoundary() const {
    return boundary_;
}

const IBoundary& Atmosphere::getRightBoundary() const {
    return boundary_;
}


// AtmosphereBoundary
//==============================================================================
Atmosphere::AtmosphereBoundary::AtmosphereBoundary(Atmosphere* owner):
    owner_(owner) {}

const Cell Atmosphere::AtmosphereBoundary::getState() const {
    return owner_->cell_;
}

void Atmosphere::AtmosphereBoundary::setFlux(const Flux& flux) {}

double Atmosphere::AtmosphereBoundary::getArea() const {
    return std::numeric_limits<double>::infinity();
}

//==============================================================================
