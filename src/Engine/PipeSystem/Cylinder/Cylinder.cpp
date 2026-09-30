// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Cylinder.hpp"
#include <utility>
#include <algorithm>

namespace GD = GasDynamics;

Cylinder::Cylinder(
    Head::Headlet& headlet,
    Block::Blocklet& blocklet
):
    headlet_(headlet), blocklet_(blocklet),
    mass_(GD::RHO_AMBIENT * getCurrentVolume()),
    energy_(GD::P_ATM / (GD::GAMMA - 1.0) * getCurrentVolume()),
    leftBoundary_(this, true), rightBoundary_(this, false),
    flux_(Flux(0.0, 0.0, 0.0)) {}

Cylinder::Cylinder(Cylinder&& other) noexcept:
    headlet_(other.headlet_), blocklet_(other.blocklet_),
    mass_(other.mass_), energy_(other.energy_),
    leftBoundary_(this, true), rightBoundary_(this, false),
    flux_(std::move(other.flux_)) {}

//=============================================================
void Cylinder::step(double dt) {
    applyFlux(dt);
}

double Cylinder::getTotalChamberVolume() const {
    return headlet_.getChamberVolume() + blocklet_.getTotalDeckVolume();
}

double Cylinder::getCompressionRatio() const {
    double totalChamberVolume = getTotalChamberVolume();
    return (blocklet_.getSweptVolume() + totalChamberVolume) / totalChamberVolume;
}

double Cylinder::getCurrentVolume() const {
    return getTotalChamberVolume() + blocklet_.getDisplacedVolume();
}

double Cylinder::calculatePressure() const {
    return (GD::GAMMA - 1.0) * energy_ / getCurrentVolume();
}

double Cylinder::calculateForceG() const {
    return calculatePressure() * blocklet_.getBoreArea();
}

double Cylinder::calculateForceI() const {
    return (calculatePressure() - GD::P_ATM) * blocklet_.getBoreArea();
}

double Cylinder::calculateTorque() const {
    return calculateForceI() * blocklet_.getLeverArm();
}

void Cylinder::applyFlux(double dt) {
    mass_ += flux_.mass * dt;
    energy_ += flux_.energy * dt;

    energy_ -= calculatePressure() * blocklet_.getPistonVelocity() * blocklet_.getBoreArea() * dt;

    mass_ = std::max(mass_, 1.0e-12);
    energy_ = std::max(energy_, 1.0e-12);

    resetFlux();
}

void Cylinder::resetFlux() {
    flux_.energy = 0.0;
    flux_.mass = 0.0;
    flux_.momentum = 0.0;
}

const IBoundary& Cylinder::getBoundary(bool isLeft) const {
    return isLeft ? leftBoundary_ : rightBoundary_;
}

// CylinderBoundary
//==============================================================================
Cylinder::CylinderBoundary::CylinderBoundary(Cylinder* owner, bool isLeft)
            : owner_(owner), isLeft_(isLeft) {}

Cell Cylinder::CylinderBoundary::getState() const {
    double rho = owner_->mass_ / owner_->getCurrentVolume();
    double p = owner_->calculatePressure();

    // rho_E = p / (gamma - 1) + 0.5 * rho * u^2..
    const double rho_E = p / (GD::GAMMA - 1.0); // + 0.5 * rho * u * u;

    return Cell(rho, 0, rho_E);
}

void Cylinder::CylinderBoundary::setFlux(const Flux& flux) const {
    double sign = isLeft_ ? 1.0 : -1.0;
    owner_->flux_.mass += sign * flux.mass;
    owner_->flux_.energy += sign * flux.energy;
}

double Cylinder::CylinderBoundary::getArea() const {
    return isLeft_
        ? owner_->headlet_.getIntakeValveArea()
        : owner_->headlet_.getExhaustValveArea();
}

double Cylinder::CylinderBoundary::getAperture() const {
    return isLeft_
        ? owner_->headlet_.getIntakeFlowArea()
        : owner_->headlet_.getExhaustFlowArea();
}

bool Cylinder::CylinderBoundary::isLeft() const {
    return isLeft_;
}
//==============================================================================
