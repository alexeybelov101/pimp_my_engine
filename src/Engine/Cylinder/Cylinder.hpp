#pragma once
#include "Head/Head.hpp"
#include "Block/Block.hpp"

class Cylinder {
public:
    Cylinder(
        Head&& head,
        Block&& block
    );

    double getTotalChamberVolume() const;
    double getCompressionRatio() const;
    double calculateTorque() const;

    void step(double angle, double omega) const;
private:
    Head head;
    Block block;

    double calculatePressure() const;
};
