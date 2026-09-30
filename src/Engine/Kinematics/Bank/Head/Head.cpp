// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Head.hpp"
#include <utility>
#include <vector>

Head::Head(
    double chamberVolume,
    Valvetrain&& intakeValvetrain,
    Valvetrain&& exhaustValvetrain
) : chamberVolume_(chamberVolume),
    intakeValvetrain_(std::move(intakeValvetrain)),
    exhaustValvetrain_(std::move(exhaustValvetrain)) {}

Head::Headlet::Headlet(
    Head* owner,
    Valvetrain::Valvetrainlet& intakeValvetrainlet,
    Valvetrain::Valvetrainlet& exhaustValvetrainlet
) : owner_(owner),
    intakeValvetrainlet_(intakeValvetrainlet),
    exhaustValvetrainlet_(exhaustValvetrainlet) {}

void Head::setHeadlets(std::vector<Headlet>&& headlets) {
    headlets_ = std::move(headlets);
}

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
