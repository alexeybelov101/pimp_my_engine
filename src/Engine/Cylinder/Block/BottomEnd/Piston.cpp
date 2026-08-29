#include "Piston.hpp"
#include <numbers>

Piston::Piston(double diameter, double compressionHeight, double deckVolume) :
    diameter(diameter), compressionHeight(compressionHeight), deckVolume(deckVolume) {}

double Piston::getBore() const {
    return diameter;
}

double Piston::getCompressionHeight() const {
    return compressionHeight;
}

double Piston::getBoreArea() const {
    return std::numbers::pi * diameter * diameter / 4;
}

double Piston::getDeckVolume() const {
    return deckVolume;
}
