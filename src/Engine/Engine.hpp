// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include "Mechanics/Mechanics.hpp"
#include "GasDynamics/GasDynamics.hpp"

class Engine {
public:
    Engine(
        std::unique_ptr<Mechanics> mechanics,
        std::unique_ptr<GasDynamics> gasDynamics
    );

    void setOmega(double omega);

    void step(double dt);

private:
    double angle_;

    std::unique_ptr<Mechanics> mechanics_;
    std::unique_ptr<GasDynamics> gasDynamics_;
};
