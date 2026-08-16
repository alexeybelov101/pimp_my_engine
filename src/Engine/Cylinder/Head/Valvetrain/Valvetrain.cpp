#include "Valvetrain.hpp"

Valvetrain::Valvetrain(Camshaft&& camshaft, std::vector<LobeGroup>&& lobeGroups):
    camshaft(std::move(camshaft)), lobeGroups(std::move(lobeGroups)) {}

double Valvetrain::getFlowAreaById(size_t lobeId, double angle) const {
    const LobeGroup& group = lobeGroups[lobeId];
    double lift = camshaft.getLift(lobeId, angle);

    double sum = 0.0;
    for (Valve valve : group.valves) {
        sum += valve.getFlowArea(lift);
    }

    return sum;
}

double Valvetrain::getTotalFlowArea(double angle) const {
    double sum = 0.0;
    for (const LobeGroup& group : lobeGroups) {
        sum += getFlowAreaById(group.lobeId, angle);
    }

    return sum;
}
