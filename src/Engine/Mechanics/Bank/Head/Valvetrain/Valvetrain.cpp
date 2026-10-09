// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Valvetrain.hpp"
#include <utility>

Valvetrain::Valvetrain(
    std::unique_ptr<Camshaft> camshaft,
    std::vector<Valve>&& valves,
    std::vector<Link>&& links
):
    camshaft_(std::move(camshaft)),
    valves_(std::move(valves)),
    links_(std::move(links)) {
        for (auto& l : links_) l.owner_ = this;
    }

//TODO: переделать, когда появится нагрузка от ГРМ
double Valvetrain::getAngle() const {
    return camshaft_->getAngle();
}

void Valvetrain::setAngle(double angle) {
    camshaft_->setAngle(angle);
}

// Link
//==============================================================================
Valvetrain::Link::Link(
    std::vector<Camshaft::Lobe*> lobes,
    std::vector<Valve*> valves
):
    owner_(nullptr),
    lobes_(lobes),
    valves_(valves) {}

double Valvetrain::Link::getTotalFlowArea() const {
    double lift = lobes_[0]->getLift(); //TODO: реализовать логику VTEC
    double sum = 0.0;
    for (auto& valve : valves_ ) {
        sum += valve->getFlowArea(lift);
    }

    return sum;
}

double Valvetrain::Link::getTotalValveArea() const {
    double sum = 0.0;
    for (const auto& valve : valves_) {
        sum += valve->getValveArea();
    }

    return sum;
}
