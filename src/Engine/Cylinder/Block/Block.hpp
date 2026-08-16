#pragma once
#include "Piston.hpp"
#include "Conrod.hpp"
#include "Crankshaft.hpp"

class Block {
public:
    Block(
        Piston&& piston,
        Conrod&& conrod,
        Crankshaft&& crankshaft
    );

    double getPistonTopPosition(double angle) const;
    double getPistonVelocity(double angle, double rpm) const;

    double getDisplacedVolume(double angle) const;
    double getSweptVolume() const;

private:
    Piston piston;
    Conrod conrod;
    Crankshaft crankshaft;
};
