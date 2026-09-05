#include "Crankshaft.hpp"
#include <cmath>

Crankshaft::Crankshaft(double radius):
    radius_(radius) {}

double Crankshaft::getRadius() const {
    return radius_;
}

double Crankshaft::getStroke() const {
    return radius_ * 2;
}

double Crankshaft::getVertical(double angle) const {
    return radius_ * std::cos(angle);
}

double Crankshaft::getHorizontal(double angle) const {
    return radius_ * std::sin(angle);
}
