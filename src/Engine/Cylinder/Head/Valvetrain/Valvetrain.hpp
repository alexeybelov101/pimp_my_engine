#pragma once
#include <vector>
#include "Camshaft.hpp"
#include "Valve.hpp"

class Valvetrain {
public:
    struct LobeGroup {
        size_t lobeId;
        std::vector<Valve> valves;
    };

    Valvetrain(
        Camshaft&& camshaft,
        std::vector<LobeGroup>&& lobeGroups
    );

    double getFlowAreaById(size_t lobeId, double angle) const;
    double getTotalFlowArea(double angle) const;

private:
    Camshaft camshaft;
    std::vector<LobeGroup> lobeGroups;
};
