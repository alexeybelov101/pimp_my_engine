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

    void do_a_barrel_roll();

private:
    std::vector<CylPos> cylPos;
};
