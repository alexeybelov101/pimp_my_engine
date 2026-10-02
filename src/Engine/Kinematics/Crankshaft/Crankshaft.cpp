// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Crankshaft.hpp"
#include <numbers>
#include <cmath>

Crankshaft::Crankshaft(
    double radius,
    std::vector<Pin>&& pins,
    Flywheel& flywheel
):
    angle_(0.0),
    radius_(radius),
    pins_(std::move(pins)),
    flywheel_(flywheel) {
        for (auto& p : pins_) p.owner_ = this;
    }

double Crankshaft::getOmega() const {
    return flywheel_.getOmega();
}

//TODO: переделать, когда появится нагрузка от ГРМ
double Crankshaft::getAngle() const {
    return angle_;
}

void Crankshaft::advance(double dt) {
    double alpha = flywheel_.getOmega() * dt;
    angle_ = fmod(
        angle_ + alpha + 4.0 * std::numbers::pi,
        4.0 * std::numbers::pi
    );
}

void Crankshaft::step(double dt) {
    flywheel_.applyTorque(torque_, dt);
    torque_ = 0.0;

    advance(dt);
}

// Pin
//==============================================================================
Crankshaft::Pin::Pin(double position):
    owner_(nullptr),
    position_(position) {}

double Crankshaft::Pin::getThrow() const {
    return owner_->radius_;
}

double Crankshaft::Pin::getAngle() const {
    return fmod(
        owner_->angle_ - position_ + 2.0 * std::numbers::pi,
        2.0 * std::numbers::pi
    );
}

double Crankshaft::Pin::getOmega() const {
    return owner_->flywheel_.getOmega();
}

void Crankshaft::Pin::setTorque(double torque) {
    owner_->torque_ += torque;
}
