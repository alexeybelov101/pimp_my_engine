// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Head.hpp"
#include <utility>
#include <vector>

Head::Head(
    double chamberVolume,
    std::unique_ptr<Valvetrain> intakeValvetrain,
    std::unique_ptr<Valvetrain> exhaustValvetrain,
    std::vector<std::unique_ptr<Headlet>> headlets
):
    chamberVolume_(chamberVolume),
    intakeValvetrain_(std::move(intakeValvetrain)),
    exhaustValvetrain_(std::move(exhaustValvetrain)),
    headlets_(std::move(headlets)) {
        for (auto& h : headlets_) h->owner_ = this;
    }

Head::Headlet::Headlet(
    Valvetrain::Valvetrainlet& intakeValvetrainlet,
    Valvetrain::Valvetrainlet& exhaustValvetrainlet
):
    owner_(nullptr),
    intakeValvetrainlet_(intakeValvetrainlet),
    exhaustValvetrainlet_(exhaustValvetrainlet) {}

double Head::Headlet::getChamberVolume() const {
    return owner_->chamberVolume_;
}

double Head::Headlet::getIntakeFlowArea() const {
    return intakeValvetrainlet_.getTotalFlowArea();
}

double Head::Headlet::getIntakeValveArea() const {
    return intakeValvetrainlet_.getTotalValveArea();
}

double Head::Headlet::getExhaustFlowArea() const {
    return exhaustValvetrainlet_.getTotalFlowArea();
}

double Head::Headlet::getExhaustValveArea() const {
    return exhaustValvetrainlet_.getTotalValveArea();
}
