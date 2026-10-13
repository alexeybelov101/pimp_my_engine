// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Distributor.hpp"
#include <cmath>
#include <numbers>
#include <iostream>

Distributor::Distributor(
    double staticAdvance,
    Shutter shutter,
    std::vector<double> contactAngles,
    std::vector<SparkPlug*> sparkPlugs,
    Coil* coil,
    Crankshaft* crankshaft
):
    staticAdvance_(staticAdvance),
    shutter_(shutter),
    contactAngles_(contactAngles),
    sparkPlugs_(sparkPlugs),
    coil_(coil),
    crankshaft_(crankshaft) {}

void Distributor::step(double dt) {
    double angle = std::fmod(
        crankshaft_->getAngle() * 0.5 + staticAdvance_ + 2.0 * std::numbers::pi,
        2.0 * std::numbers::pi
    );

    if (checkHallSensor(angle)) {
        coil_.charge(dt);
        std::cout << getClosestContact(angle) << std::endl;
    } else {
        coil_.discharge(dt);
    }
}

bool Distributor::checkHallSensor(double angle) {
    double period = shutter_.plateExtent_ + shutter_.windowExtent_;
    double local = std::fmod(angle, period);
    return local < shutter_.plateExtent_ ? true : false;
}

size_t Distributor::getClosestContact(double angle) {
    size_t best_id = 0;
    double best = 1.0e6;

    for (size_t id = 0; id < contactAngles_.size(); ++id) {
        double current = std::fabs(contactAngles_[id] - angle);
        if (current < best) {
            best = current;
            best_id = id;
        }
    }

    return best_id;
}
