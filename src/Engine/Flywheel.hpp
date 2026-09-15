// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Flywheel {
public:
    Flywheel(double mass, double radius);

    void applyTorque(double torque, double dt);

    double getInertia() const;

    double getOmega() const;
    void setOmega(double omega);
private:
    double mass_;
    double radius_;
    double omega_;
};
