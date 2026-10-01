// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <memory>
#include "Kinematics/Kinematics.hpp"
#include "PipeSystem/PipeSystem.hpp"

class Engine {
public:
    Engine(
        std::unique_ptr<Kinematics> kinematics,
        std::unique_ptr<PipeSystem> pipeSystem
    );

    void setOmega(double omega);

    void step(double dt);

private:
    double angle_;

    std::unique_ptr<Kinematics> kinematics_;
    std::unique_ptr<PipeSystem> pipeSystem_;
};
