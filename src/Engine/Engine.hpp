#pragma once
#include "Cylinder/Cylinder.hpp"
#include "Flywheel.hpp"

class Engine {
public:
    Engine(std::vector<Cylinder>&& cylinders, Flywheel&& flywheel);

    void setOmega(double omega);

    void step(double dt);

private:
    double angle_;

    std::vector<Cylinder> cylinders_;
    Flywheel flywheel_;
};
