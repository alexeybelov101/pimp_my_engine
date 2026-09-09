#include "Atmosphere.hpp"
#include "../../Constants/GasDynamics.hpp"
#include <limits>

namespace GD = GasDynamics;

Atmosphere::Atmosphere():
    boundaries_{
        AtmosphereBoundary(this, true),
        AtmosphereBoundary(this, false)
    },
    cell_(
        GD::RHO_AMBIENT,
        0.0,
        GD::P_ATM / (GD::GAMMA - 1.0)
    ) {}

const IBoundary& Atmosphere::getLeftBoundary() const {
    return boundaries_.first;
}

const IBoundary& Atmosphere::getRightBoundary() const {
    return boundaries_.second;
}


// AtmosphereBoundary
//==============================================================================
Atmosphere::AtmosphereBoundary::AtmosphereBoundary(Atmosphere* owner, bool isLeft):
    owner_(owner), isLeft_(isLeft) {}

const Cell Atmosphere::AtmosphereBoundary::getState() const {
    return owner_->cell_;
}

void Atmosphere::AtmosphereBoundary::setFlux(const Flux& flux) {}

double Atmosphere::AtmosphereBoundary::getArea() const {
    return std::numeric_limits<double>::infinity();
}

bool Atmosphere::AtmosphereBoundary::isLeft() const {
    return isLeft_;
}

//==============================================================================
