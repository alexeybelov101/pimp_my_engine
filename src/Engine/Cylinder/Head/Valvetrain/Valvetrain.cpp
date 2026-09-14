#include "Valvetrain.hpp"

Valvetrain::Valvetrain(
    Camshaft&& camshaft,
    std::vector<std::vector<Valve>>&& lobeValves
):
    camshaft_(std::move(camshaft)),
    lobeValves_(std::move(lobeValves)) {}

double Valvetrain::getFlowAreaByLobe(size_t lobeId, double angle) const {
    double lift = camshaft_.getLift(lobeId, angle);

    double sum = 0.0;
    for (const Valve& valve : lobeValves_[lobeId]) {
        sum += valve.getFlowArea(lift);
    }

    return sum;
}

double Valvetrain::getTotalFlowArea(double angle) const {
    double sum = 0.0;

    for (size_t lobeId = 0; lobeId < lobeValves_.size(); ++lobeId) {
        sum += getFlowAreaByLobe(lobeId, angle);
    }

    return sum;
}

double Valvetrain::getLift(double angle) const {
    return camshaft_.getLift(0, angle);
}

double Valvetrain::getTotalValveArea() const {
    double sum = 0.0;
    for (const auto& valves : lobeValves_) {
        for (const auto& valve : valves)
        sum += valve.getValveArea();
    }

    return sum;
}
