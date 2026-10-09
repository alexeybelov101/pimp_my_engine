// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Camshaft.hpp"
#include <numbers>
#include <cmath>

Camshaft::Camshaft(
    std::vector<Lobe>&& lobes
):
    angle_(0.0),
    lobes_(std::move(lobes)) {
        for (auto& l : lobes_) l.owner_ = this;
    }

double Camshaft::getAngle() const {
    return angle_;
}

void Camshaft::setAngle(double angle) {
    angle_ = angle;
}

// Lobe
//==============================================================================
Camshaft::Lobe::Lobe(
    double offset,
    double maxLift,
    double duration
):
    owner_(nullptr),
    offset_(offset),
    maxLift_(maxLift),
    duration_(duration) {}

double Camshaft::Lobe::getLift() const {
    double angle = fmod(
        owner_->angle_ - offset_ + 2.0 * std::numbers::pi,
        2.0 * std::numbers::pi
    );;

    if (angle > duration_) return 0.0;

    double phase = (angle / duration_) * std::numbers::pi;

    return maxLift_ * std::sin(phase);
}
