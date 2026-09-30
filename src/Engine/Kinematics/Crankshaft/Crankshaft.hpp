// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Engine/Kinematics/Flywheel/Flywheel.hpp"
#include <vector>

class Crankshaft {
public:
    class Pin {
    public:
        Pin(Crankshaft* owner, double position);

        double getThrow() const;
        double getAngle() const;
        double getOmega() const;

        void setTorque(double torque);

    private:
        Crankshaft* owner_;
        double position_;
    };

    Crankshaft(double angle, double radius, std::vector<Pin>&& pins, Flywheel& flywheel);

    void addAngle(double angle);
    void step(double dt);

private:
    double angle_;
    double radius_;
    double torque_;

    std::vector<Pin> pins_;
    Flywheel& flywheel_;
};
