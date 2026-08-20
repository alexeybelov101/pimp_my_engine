#include "Cylinder.hpp"
#include <utility>

Cylinder::Cylinder(double gasketHeight, Head&& head, Block&& block):
    gasketHeight(gasketHeight),
    head(std::move(head)),
    block(std::move(block)) {}

double Cylinder::getTotalChamberVolume() const {
    return head.getChamberVolume() + block.getTotalDeckVolume() + gasketHeight * block.getBoreArea();
}

double Cylinder::getCompressionRatio() const {
    double totalChamberVolume = getTotalChamberVolume();
    double sweptVolume = block.getSweptVolume();

    return (sweptVolume + totalChamberVolume) / totalChamberVolume;
}
