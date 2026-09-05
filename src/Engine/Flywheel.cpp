#include "Flywheel.hpp"

Flywheel::Flywheel(double mass, double raduis):
    mass_(mass), radius_(raduis), omega_(0.0) {}

void Flywheel::applyTorque(double torque, double dt) {
    omega_ += torque / (0.5 * mass_ * radius_ * radius_) * dt;
}

double Flywheel::getInertia() const {
    return 0.5 * mass_ * radius_ * radius_;
}

double Flywheel::getOmega() const {
    return omega_;
}

void Flywheel::setOmega(double omega) {
    omega_ = omega;
}
