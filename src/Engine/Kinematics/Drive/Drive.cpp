// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Drive.hpp"
#include <vector>

Drive::Drive(
    Flywheel& flywheel,
    Crankshaft& crankshaft,
    std::vector<Valvetrain*> valvetrains
):
    flywheel_(flywheel),
    crankshaft_(crankshaft),
    valvetrains_(valvetrains) {}

void Drive::step(double dt) {
    double angle = flywheel_.getOmega() * dt;
    crankshaft_.addAngle(angle);
    for (auto& valvetrain : valvetrains_) {
        valvetrain->addAngle(angle * 0.5);
    }
}
