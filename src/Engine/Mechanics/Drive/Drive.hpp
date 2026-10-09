// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Crankshaft/Crankshaft.hpp"
#include "Engine/Mechanics/Bank/Head/Valvetrain/Valvetrain.hpp"
#include <vector>

class Drive {
public:
    Drive(
        Crankshaft* crankshaft,
        std::vector<Valvetrain*>&& valvetrains
    );

    void step(double dt);

private:
    Crankshaft* crankshaft_;
    std::vector<Valvetrain*> valvetrains_;
};
