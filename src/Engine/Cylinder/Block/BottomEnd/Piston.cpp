#include "Piston.hpp"
#include <cmath>

Piston::Piston(double diameter, double compressionHeight, double deckVolume) :
    diameter(diameter), compressionHeight(compressionHeight), deckVolume(deckVolume) {}

double Piston::getBore() const {
    return diameter;
}

double Piston::getCompressionHeight() const {
    return compressionHeight;
}

double Piston::getBoreArea() const {
    return M_PI * diameter * diameter / 4;
}

double Piston::getDeckVolume() const {
    return deckVolume;
}
