// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Kinematics.hpp"
#include <utility>

Kinematics::Kinematics(
    Flywheel&& flywheel,
    Crankshaft&& crankshaft,
    std::vector<Bank>&& banks,
    Drive&& drive
):
    flywheel_(std::move(flywheel)),
    crankshaft_(std::move(crankshaft)),
    banks_(std::move(banks)),
    drive_(std::move(drive)) {}

void Kinematics::step(double dt) {
    crankshaft_.step(dt);
    drive_.step(dt);
}
