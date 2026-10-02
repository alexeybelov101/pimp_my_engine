// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Kinematics/Crankshaft/Crankshaft.hpp"
#include "Camshaft/Camshaft.hpp"
#include "Valve.hpp"
#include <vector>

class Valvetrain {
public:
    class Valvetrainlet {
    public:
        Valvetrainlet(
            Valvetrain* owner,
            Camshaft&& camshaft,
            double position,
            std::vector<std::vector<Valve>>&& lobeValves
        );

        double getAngle() const;
        double getTotalFlowArea() const;
        double getTotalValveArea() const;

    private:
        Valvetrain* owner_;
        Camshaft camshaft_;
        double position_;
        std::vector<std::vector<Valve>> lobeValves_;
    };

    Valvetrain(
        std::vector<Valvetrainlet>&& valvetrainlets,
        Crankshaft& crankshaft
    );

    double getAngle() const;
    void setAngle(double angle);

private:
    double angle_;
    std::vector<Valvetrainlet> valvetrainlets_;
    Crankshaft& crankshaft_;
};
