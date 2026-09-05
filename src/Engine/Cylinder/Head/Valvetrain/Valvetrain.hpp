#pragma once
#include <vector>
#include "Camshaft/Camshaft.hpp"
#include "Valve.hpp"

class Valvetrain {
public:
    Valvetrain(
        Camshaft&& camshaft,
        std::vector<std::vector<Valve>>&& lobeValves
    );

    double getFlowAreaByLobe(size_t lobeId, double angle) const;
    double getTotalFlowArea(double angle) const;

    double getLift(double angle) const;

private:
    Camshaft camshaft_;
    std::vector<std::vector<Valve>> lobeValves_;
};
