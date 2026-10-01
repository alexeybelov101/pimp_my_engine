// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Crankshaft.hpp"
#include <numbers>
#include <cmath>

Crankshaft::Crankshaft(
    double angle,
    double radius,
    std::vector<Pin>&& pins,
    Flywheel& flywheel
):
    angle_(angle),
    radius_(radius),
    pins_(std::move(pins)),
    flywheel_(flywheel) {}

void Crankshaft::addAngle(double angle) {
    angle_ += angle;
    angle_ = fmod(angle_, 2.0 * std::numbers::pi);
}

void Crankshaft::step(double dt) {
    flywheel_.applyTorque(torque_, dt);
    torque_ = 0.0;
}

double Crankshaft::Pin::getThrow() const {
    return owner_->radius_;
}

double Crankshaft::Pin::getAngle() const {
    return owner_->angle_ - position_;
}

double Crankshaft::Pin::getOmega() const {
    return owner_->flywheel_.getOmega();
}

void Crankshaft::Pin::setTorque(double torque) {
    owner_->torque_ += torque;
}
