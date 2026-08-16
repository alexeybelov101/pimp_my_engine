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

    double getDisplacedVolume(double angle) const;
    double getSweptVolume() const;

private:
    double height;
    Piston piston;
    Conrod conrod;
    Crankshaft crankshaft;
};
