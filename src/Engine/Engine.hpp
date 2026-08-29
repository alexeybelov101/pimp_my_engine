#pragma once
#include "Cylinder/Cylinder.hpp"

class Engine {
public:
    struct CylPos {
        Cylinder cylinder;
        double position;

        CylPos(Cylinder&& cyl, double pos)
            : cylinder(std::move(cyl)), position(pos) {}
    };

    Engine(std::vector<CylPos>&& cylPos);

    void setOmega(double newOmega);

    void step(double dt);

private:
    double omega = 0.0;
    double angle = 0.0;
    std::vector<CylPos> cylPos;
};
