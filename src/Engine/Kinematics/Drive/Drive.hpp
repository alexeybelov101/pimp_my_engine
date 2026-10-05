// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Kinematics/Crankshaft/Crankshaft.hpp"
#include "Engine/Kinematics/Bank/Head/Valvetrain/Valvetrain.hpp"
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
