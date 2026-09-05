#include "Valve.hpp"
#include <numbers>

Valve::Valve(double headDiameter, double sinSeatA, double cosSeatA):
    headDiameter_(headDiameter), sinSeatA_(sinSeatA), cosSeatA_(cosSeatA) {}

double Valve::getFlowArea(double lift) const {
    return std::numbers::pi * lift * cosSeatA_ * (headDiameter_ - lift * sinSeatA_ * cosSeatA_);
}
