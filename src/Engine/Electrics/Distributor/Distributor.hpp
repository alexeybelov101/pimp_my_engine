// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Mechanics/Crankshaft/Crankshaft.hpp"
#include "Engine/Electrics/Plugs/SparkPlug.hpp"
#include "Engine/Electrics/Coil/Coil.hpp"
#include <vector>

class Distributor {
public:
    struct Shutter {
        double plateExtent_;
        double windowExtent_;
    };

    Distributor(
        double staticAdvance,
        Shutter shutter,
        std::vector<double> contactAngles,
        std::vector<SparkPlug*> sparkPlugs,
        Coil* coil,
        Crankshaft* crankshaft
    );

    bool checkHallSensor(double angle);
    size_t getClosestContact(double angle);

    void step(double dt);
private:
    const double staticAdvance_;
    const Shutter shutter_;
    const std::vector<double> contactAngles_;
    std::vector<SparkPlug*> sparkPlugs_;
    Coil* coil_;
    Crankshaft* crankshaft_;
};
