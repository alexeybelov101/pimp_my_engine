// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Kinematics.hpp"
#include <utility>

Kinematics::Kinematics(
    std::unique_ptr<Flywheel> flywheel,
    std::unique_ptr<Crankshaft> crankshaft,
    std::vector<std::unique_ptr<Bank>> banks,
    std::unique_ptr<Drive> drive
):
    flywheel_(std::move(flywheel)),
    crankshaft_(std::move(crankshaft)),
    banks_(std::move(banks)),
    drive_(std::move(drive)) {}

void Kinematics::setOmega(double omega) {
    flywheel_->setOmega(omega);
}

void Kinematics::step(double dt) {
    crankshaft_->step(dt);
    drive_->step(dt);
}
