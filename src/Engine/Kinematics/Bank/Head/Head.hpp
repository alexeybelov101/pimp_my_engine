// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Valvetrain/Valvetrain.hpp"
#include <memory>
#include <vector>

class Head {
public:
    class Headlet {
    public:
        Headlet(
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

        friend class Head;
    };

    Head(
        double chamberVolume,
        std::unique_ptr<Valvetrain> intakeValvetrain,
        std::unique_ptr<Valvetrain> exhaustValvetrain,
        std::vector<std::unique_ptr<Headlet>> headlets_
    );

private:
    double chamberVolume_;
    std::unique_ptr<Valvetrain> intakeValvetrain_;
    std::unique_ptr<Valvetrain> exhaustValvetrain_;
    std::vector<std::unique_ptr<Headlet>> headlets_;
};
