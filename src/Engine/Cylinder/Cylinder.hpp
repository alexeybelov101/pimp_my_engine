#pragma once
#include "Head/Head.hpp"
#include "Block/Block.hpp"

class Cylinder {
public:
    Cylinder(
        double gasketHeight,
        Head&& head,
        Block&& block
    );

    double getGasketChamber() const;
    double getTotalChamberVolume() const;
    double getCompressionRatio() const;
    double calculateTorque() const;

private:
    double gasketHeight;
    Head head;
    Block block;

    double calculatePressure() const;
};
