#include "Camlobe.hpp"
#include <numbers>
#include <cmath>

Camlobe::Camlobe(double maxLift, double duration):
    maxLift(maxLift), duration(duration) {}

double Camlobe::getLift(double angle) const {
    if (angle < 0 || angle > duration) return 0.0;

    double phase = (angle / duration) * std::numbers::pi;

    return maxLift * std::sin(phase);
}
