// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Drive.hpp"

Drive::Drive(
    Crankshaft& crankshaft,
    std::vector<Valvetrain*> valvetrains
):
    crankshaft_(crankshaft),
    valvetrains_(valvetrains) {}

void Drive::step(double /*dt*/) {
    double angle = crankshaft_.getAngle();

    for (auto& valvetrain : valvetrains_) {
        valvetrain->setAngle(angle * 0.5);
    }
}
