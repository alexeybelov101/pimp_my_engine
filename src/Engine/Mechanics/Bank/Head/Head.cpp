// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Head.hpp"
#include <utility>
#include <vector>

Head::Head(
    double chamberVolume,
    std::unique_ptr<Valvetrain> valvetrain,
    std::vector<Headlet>&& headlets
):
    chamberVolume_(chamberVolume),
    valvetrain_(std::move(valvetrain)),
    headlets_(std::move(headlets)) {
        for (auto& h : headlets_) h.owner_ = this;
    }

// Headlet
//==============================================================================
Head::Headlet::Headlet(
    Valvetrain::Link* intakeLink,
    Valvetrain::Link* exhaustLink
):
    owner_(nullptr),
    intakeLink_(intakeLink),
    exhaustLink_(exhaustLink) {}

double Head::Headlet::getChamberVolume() const {
    return owner_->chamberVolume_;
}

double Head::Headlet::getIntakeFlowArea() const {
    return intakeLink_->getTotalFlowArea();
}

double Head::Headlet::getIntakeValveArea() const {
    return intakeLink_->getTotalValveArea();
}

double Head::Headlet::getExhaustFlowArea() const {
    return exhaustLink_->getTotalFlowArea();
}

double Head::Headlet::getExhaustValveArea() const {
    return exhaustLink_->getTotalValveArea();
}
