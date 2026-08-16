#include "Crankshaft.hpp"
#include <cmath>

Crankshaft::Crankshaft(double radius):
    radius(radius) {}

double Crankshaft::getRadius() const {
    return radius;
}

double Crankshaft::getStroke() const {
    return radius * 2;
}

double Crankshaft::getVertical(double angle) const {
    return radius * std::cos(angle);
}

double Crankshaft::getHorizontal(double angle) const {
    return radius * std::sin(angle);
}

Crankshaft::Projections Crankshaft::getProjections(double angle) const {
    double sinA, cosA;
    sincos(angle, &sinA, &cosA);

    return {
        radius * sinA,
        radius * cosA
    };
}
