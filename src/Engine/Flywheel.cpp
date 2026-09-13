#include "Flywheel.hpp"
#include <cmath>

Flywheel::Flywheel(double mass, double raduis):
    mass_(mass), radius_(raduis), omega_(0.0) {}

void Flywheel::applyTorque(double torque, double dt) {
    double inertia = getInertia();

    omega_ += torque * 0.95 / inertia * dt;

    // if (std::fabs(omega_) < 1.0e-3 &&
    //     std::fabs(torque) < 0.1) {
    //     omega_ = 0.0;
    // }
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
