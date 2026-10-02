// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Valvetrain.hpp"
#include <numbers>
#include <cmath>

Valvetrain::Valvetrain(
    std::vector<Valvetrainlet>&& valvetrainlets,
    Crankshaft& crankshaft
):
    angle_(0.0),
    valvetrainlets_(std::move(valvetrainlets)),
    crankshaft_(crankshaft) {}

//TODO: переделать, когда появится нагрузка от ГРМ
double Valvetrain::getAngle() const {
    return angle_;
}

void Valvetrain::setAngle(double angle) {
    angle_ = angle;
}


// Valvetrainlet
//==============================================================================
Valvetrain::Valvetrainlet::Valvetrainlet(
    Valvetrain* owner,
    Camshaft&& camshaft,
    double position,
    std::vector<std::vector<Valve>>&& lobeValves
):
    owner_(owner),
    camshaft_(std::move(camshaft)),
    position_(position),
    lobeValves_(std::move(lobeValves)) {}

double Valvetrain::Valvetrainlet::getAngle() const {
    return fmod(
        owner_->angle_ - position_ + 2.0 * std::numbers::pi,
        2.0 * std::numbers::pi
    );
}

double Valvetrain::Valvetrainlet::getTotalFlowArea() const {
    double angle = getAngle();
    double sum = 0.0;
    for (size_t lobeId = 0; lobeId < lobeValves_.size(); ++lobeId) {
        double lift = camshaft_.getLift(lobeId, angle);
        for (const Valve& valve : lobeValves_[lobeId]) {
            sum += valve.getFlowArea(lift);
        }
    }

    return sum;
}

double Valvetrain::Valvetrainlet::getTotalValveArea() const {
    double sum = 0.0;
    for (const auto& valves : lobeValves_) {
        for (const auto& valve : valves) {
            sum += valve.getValveArea();
        }
    }

    return sum;
}
