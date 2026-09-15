// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Valvetrain/Valvetrain.hpp"

class Head {
public:
    Head(
        double chamberVolume,
        Valvetrain&& intakeValvetrain,
        Valvetrain&& exhaustValvetrain
    );

    double getChamberVolume() const;

    double getIntakeLift(double angle) const;
    double getIntakeFlowArea(double angle) const;
    double getIntakeValveArea() const;

    double getExhaustLift(double angle) const;
    double getExhaustFlowArea(double angle) const;
    double getExhaustValveArea() const;

private:
    double chamberVolume_;
    Valvetrain intakeValvetrain_;
    Valvetrain exhaustValvetrain_;
};
