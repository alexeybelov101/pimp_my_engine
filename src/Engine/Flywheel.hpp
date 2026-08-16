#pragma once

class Flywheel {
public:
    explicit Flywheel(double mass);

    double get_mass() const { return mass; }

private:
    double mass;
};
