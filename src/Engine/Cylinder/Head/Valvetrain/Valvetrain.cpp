#include "Valvetrain.hpp"

Valvetrain::Valvetrain(Camshaft&& camshaft,  std::vector<std::vector<Valve>>&& lobeValves):
    camshaft(std::move(camshaft)), lobeValves(std::move(lobeValves)) {}

double Valvetrain::getFlowAreaByLobe(size_t lobeId, double angle) const {
    double lift = camshaft.getLift(lobeId, angle);

    double sum = 0.0;
    for (const Valve& valve : lobeValves[lobeId]) {
        sum += valve.getFlowArea(lift);
    }

    return sum;
}

double Valvetrain::getTotalFlowArea(double angle) const {
    double sum = 0.0;
    for (size_t lobeId = 0; lobeId < lobeValves.size(); lobeId++) {
        sum += getFlowAreaByLobe(lobeId, angle);
    }

    return sum;
}
