#include "Pipe.hpp"
#include <algorithm>
#include <cmath>

Pipe::Pipe(int id) : id(id), length(0.0), radius(0.0), pressure(0.0) {}

Pipe::Pipe(int id, double length, double radius, double pressure)
    : id(id), length(length), radius(radius), pressure(pressure) {}

Pipe::~Pipe() {}

size_t Pipe::getParentCount() const {
    return parents.size();
}

size_t Pipe::getChildCount() const {
    return children.size();
}

bool Pipe::hasParent(Pipe* parent) const {
    return std::find(parents.begin(), parents.end(), parent) != parents.end();
}

bool Pipe::hasChild(Pipe* child) const {
    return std::find(children.begin(), children.end(), child) != children.end();
}

double Pipe::calculatePressureDrop(double flowRate) const {
    if (radius <= 0.0) return 0.0;
    return (length / std::pow(radius, 4)) * flowRate;
}

void Pipe::propagateForward(double inputPressure) {
    // Устанавливаем давление на текущей трубе
    this->pressure = inputPressure;

    // Если есть дети, распространяем давление дальше
    double flowRate = 1.0;
    double pressureDrop = calculatePressureDrop(flowRate);
    double outputPressure = inputPressure - pressureDrop;

    for (Pipe* child : children) {
        child->propagateForward(outputPressure);
    }
}

void Pipe::propagateBackward(double inputPressure) {
    // Устанавливаем давление на текущей трубе
    this->pressure = inputPressure;

    // Если есть родители, распространяем давление назад
    double flowRate = 1.0;
    double pressureDrop = calculatePressureDrop(flowRate);
    double outputPressure = inputPressure + pressureDrop;

    for (Pipe* parent : parents) {
        parent->propagateBackward(outputPressure);
    }
}
