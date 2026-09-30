// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <vector>
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/Bank.hpp"
#include "Drive/Drive.hpp"

class Kinematics {
public:
    Kinematics(
        Flywheel&& flywheel,
        Crankshaft&& crankshaft,
        std::vector<Bank>&& banks,
        Drive&& drive
    );

    void step(double dt);

private:
    Flywheel flywheel_;
    Crankshaft crankshaft_;
    std::vector<Bank> banks_;
    Drive drive_;
};
