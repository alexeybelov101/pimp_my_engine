#include "Cylinder.hpp"
#include <utility>

Cylinder::Cylinder(Head&& head, Block&& block):
    head(std::move(head)),
    block(std::move(block)) {}

double Cylinder::getTotalChamberVolume() const {
    return head.getChamberVolume() + block.getTotalDeckVolume();
}

double Cylinder::getCompressionRatio() const {
    double totalChamberVolume = getTotalChamberVolume();
    double sweptVolume = block.getSweptVolume();

    return (sweptVolume + totalChamberVolume) / totalChamberVolume;
}

void Cylinder::step(double angle, double omega) const {
    head.getIntakeLift(angle / 2.0);
    head.getExhaustLift(angle / 2.0);

    head.getIntakeFlowArea(angle / 2.0);
    head.getExhaustFlowArea(angle / 2.0);

    block.getDisplacedVolume(angle);
    block.getLeverArm(angle);
    block.getPistonTopPosition(angle);
    block.getPistonVelocity(angle, omega);
}
