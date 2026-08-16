#include "Valve.hpp"
#include <cmath>

Valve::Valve(double headDiameter, double seatAngle):
    headDiameter(headDiameter), seatAngle(seatAngle) {}

double Valve::getFlowArea(double lift) const {
    const double alphaRad = seatAngle * M_PI / 180.0;
    const double cosA = cos(alphaRad);
    const double sinA = sin(alphaRad);

    return M_PI * lift * cosA * (headDiameter - lift * sinA * cosA);
}
