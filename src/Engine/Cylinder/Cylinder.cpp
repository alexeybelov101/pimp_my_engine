#include "Cylinder.hpp"
#include <utility>
#include <algorithm>

#include <iostream>

namespace GD = GasDynamics;

Cylinder::Cylinder(Head&& head, Block&& block, double offset):
    offset_(offset), angle_(0.0), omega_(0.0),
    head_(std::move(head)), block_(std::move(block)),
    mass_(GD::RHO_AMBIENT * getCurrentVolume()),
    energy_(GD::P_ATM / (GD::GAMMA - 1.0) * getCurrentVolume()),
    leftBoundary_(this, true), rightBoundary_(this, false),
    flux_(Flux(0.0, 0.0, 0.0)) {}

Cylinder::Cylinder(Cylinder&& other) noexcept:
    offset_(other.offset_), angle_(other.angle_), omega_(other.omega_),
    head_(std::move(other.head_)), block_(std::move(other.block_)),
    mass_(other.mass_), energy_(other.energy_),
    leftBoundary_(this, true), rightBoundary_(this, false),
    flux_(std::move(other.flux_)) {}

void Cylinder::setOmega(double omega) {
    omega_ = omega;
}

void Cylinder::setKinematics(double angle, double omega) {
    angle_ = angle;
    omega_ = omega;
}

void Cylinder::step(double dt) {
    std::cout << "angle: " << angle_ / std::numbers::pi * 180 << std::endl;
    std::cout << "offset: " << offset_ << std::endl;
    std::cout << "intake lift: " << head_.getIntakeLift((angle_ - offset_) / 2.0) << std::endl;
    std::cout << "exhaust lift: " << head_.getExhaustLift((angle_ - offset_) / 2.0) << std::endl;

// std::cout << "energy (before flux): " << energy_ << std::endl;
// std::cout << "mass (before flux): " << mass_ << std::endl;

    applyFlux(dt);
    // dW = P * dV = P * (S * v_piston * dt)
    // dU = dQ - dW

// std::cout << "energy (after flux): " << energy_ << std::endl;
// std::cout << "mass (after flux): " << mass_ << std::endl;

    energy_ -= calculateForceG() * block_.getPistonVelocity(angle_ - offset_, omega_) * dt;

// std::cout << "energy (after gas work): " << energy_ << std::endl;
// std::cout << "mass (after gas work): " << mass_ << std::endl;
}

double Cylinder::getTotalChamberVolume() const {
    return head_.getChamberVolume() + block_.getTotalDeckVolume();
}

double Cylinder::getCompressionRatio() const {
    double totalChamberVolume = getTotalChamberVolume();

    return (block_.getSweptVolume() + totalChamberVolume) / totalChamberVolume;
}

double Cylinder::getCurrentVolume() const {
    return getTotalChamberVolume() + block_.getDisplacedVolume(angle_ - offset_);
}

double Cylinder::calculatePressure() const {
    return (GD::GAMMA - 1.0) * energy_ / getCurrentVolume();
}

double Cylinder::calculateForceG() const {
    return calculatePressure() * block_.getBoreArea();
}

double Cylinder::calculateForceI() const {
    return (calculatePressure() - GD::P_ATM) * block_.getBoreArea();
}

double Cylinder::calculateTorque() const {
    return calculateForceI() * block_.getLeverArm(angle_ - offset_);
}

void Cylinder::applyFlux(double dt) {
    std::cout << "flux_mass * dt: " << flux_.mass * dt << std::endl;
    std::cout << "flux_energy * dt: " << flux_.energy * dt << std::endl;
    std::cout << "flux_momentum * dt: " << flux_.momentum * dt << std::endl;

    mass_ += flux_.mass * dt;
    energy_ += flux_.energy * dt;

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

    // rho_E = p / (gamma - 1) + 0.5 * rho * u^2. При u=0 второе слагаемое равно 0.
    double rho_E = p / (GD::GAMMA - 1.0);

    return Cell(rho, 0.0, rho_E);
}

void Cylinder::CylinderBoundary::setFlux(const Flux& flux) const {
    double sign = isLeft_ ? 1.0 : -1.0;
    owner_->flux_.mass += sign * flux.mass;
    owner_->flux_.energy += sign * flux.energy;
}

double Cylinder::CylinderBoundary::getArea() const {
    return isLeft_
        ? owner_->head_.getIntakeFlowArea((owner_->angle_ - owner_->offset_) / 2.0)
        : owner_->head_.getExhaustFlowArea((owner_->angle_ - owner_->offset_) / 2.0);
}

bool Cylinder::CylinderBoundary::isLeft() const {
    return isLeft_;
}
//==============================================================================
