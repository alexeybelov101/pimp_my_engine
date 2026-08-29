#include "Valve.hpp"
#include <numbers>

Valve::Valve(double headDiameter, double sinSeatA, double cosSeatA):
    headDiameter(headDiameter), sinSeatA(sinSeatA), cosSeatA(cosSeatA) {}

double Valve::getFlowArea(double lift) const {
    return std::numbers::pi * lift * cosSeatA * (headDiameter - lift * sinSeatA * cosSeatA);
}
