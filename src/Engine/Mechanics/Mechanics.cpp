// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Mechanics.hpp"
#include <utility>

Mechanics::Mechanics(
    std::unique_ptr<Flywheel>&& flywheel,
    std::unique_ptr<Crankshaft>&& crankshaft,
    std::vector<std::unique_ptr<Bank>>&& banks,
    Drive&& drive
):
    flywheel_(std::move(flywheel)),
    crankshaft_(std::move(crankshaft)),
    banks_(std::move(banks)),
    drive_(std::move(drive)) {}

void Mechanics::setOmega(double omega) {
    flywheel_->setOmega(omega);
}

void Mechanics::step(double dt) {
    crankshaft_->step(dt);
    drive_.step(dt);
}

