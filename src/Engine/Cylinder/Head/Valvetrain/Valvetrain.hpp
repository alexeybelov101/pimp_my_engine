// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Camshaft/Camshaft.hpp"
#include "Valve.hpp"
#include <vector>

class Valvetrain {
public:
    Valvetrain(
        Camshaft&& camshaft,
        std::vector<std::vector<Valve>>&& lobeValves
    );

    double getFlowAreaByLobe(size_t lobeId, double angle) const;
    double getTotalFlowArea(double angle) const;
    double getTotalValveArea() const;

    double getLift(double angle) const;

private:
    Camshaft camshaft_;
    std::vector<std::vector<Valve>> lobeValves_;
};
