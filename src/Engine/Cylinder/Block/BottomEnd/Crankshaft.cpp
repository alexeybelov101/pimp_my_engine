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
