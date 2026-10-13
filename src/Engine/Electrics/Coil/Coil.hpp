#pragma once

class Coil {
public:
    struct Winding {
        double resistance;
        double inductance;
        int turns;
    };

    Coil(
        Winding primary,
        Winding secondary
    );

    void charge(double dt);
    double discharge(double dt);

private:
    Winding primary_;
    Winding secondary_;
};
