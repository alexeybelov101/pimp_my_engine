// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include <vector>

class Head {
public:
    class Headlet {
    public:
        Headlet(
            Head* owner,
            Valvetrain::Valvetrainlet& intakeValvetrainlet,
            Valvetrain::Valvetrainlet& exhaustValvetrainlet
        );

        double getChamberVolume() const;

        double getIntakeFlowArea() const;
        double getIntakeValveArea() const;

        double getExhaustFlowArea() const;
        double getExhaustValveArea() const;
    private:
        Head* owner_;
        Valvetrain::Valvetrainlet& intakeValvetrainlet_;
        Valvetrain::Valvetrainlet& exhaustValvetrainlet_;
    };

    Head(
        double chamberVolume,
        Valvetrain&& intakeValvetrain,
        Valvetrain&& exhaustValvetrain
    );

private:
    void setHeadlets(std::vector<Headlet>&& headlets);

    double chamberVolume_;
    Valvetrain intakeValvetrain_;
    Valvetrain exhaustValvetrain_;
    std::vector<Headlet> headlets_;
};
