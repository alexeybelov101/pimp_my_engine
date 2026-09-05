#include "Piston.hpp"
#include <numbers>

Piston::Piston(double diameter, double compressionHeight, double deckVolume) :
    diameter_(diameter), compressionHeight_(compressionHeight), deckVolume_(deckVolume) {}

double Piston::getBore() const {
    return diameter_;
}

double Piston::getCompressionHeight() const {
    return compressionHeight_;
}

double Piston::getBoreArea() const {
    return std::numbers::pi * diameter_ * diameter_ / 4;
}

double Piston::getDeckVolume() const {
    return deckVolume_;
}
