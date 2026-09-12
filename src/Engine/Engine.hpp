#pragma once
#include "Cylinder/Cylinder.hpp"
#include "Flywheel.hpp"
#include "Pipes/PipeSystem.hpp"
#include <memory>

class Engine {
public:
    Engine(
        std::vector<std::unique_ptr<Cylinder>> cylinders,
        std::unique_ptr<Flywheel> flywheel,
        std::unique_ptr<PipeSystem> pipeSystem
    );

    void setOmega(double omega);

    void step(double dt);

private:
    double angle_;

    std::vector<std::unique_ptr<Cylinder>> cylinders_;
    std::unique_ptr<Flywheel> flywheel_;
    std::unique_ptr<PipeSystem> pipeSystem_;
};
