#pragma once
#include "BottomEnd/Piston.hpp"
#include "BottomEnd/Conrod.hpp"
#include "BottomEnd/Crankshaft.hpp"

class Block {
public:
    Block(
        double height,
        Piston&& piston,
        Conrod&& conrod,
        Crankshaft&& crankshaft
    );

    double getPistonTopPosition(double angle) const;
    double getPistonVelocity(double angle, double rpm) const;
    double getLeverArm(double angle) const;
    double getDisplacedVolume(double angle) const;
    double getSweptVolume() const;
    double getTDC() const;
    double getBDC() const;

private:
    double height;
    Piston piston;
    Conrod conrod;
    Crankshaft crankshaft;
};
