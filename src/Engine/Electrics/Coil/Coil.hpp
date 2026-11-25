#pragma once
#include <cstddef>

class Coil {
public:
    struct Winding {
        const double R;
        const double L;
        const double C;
        const size_t turns;

        double I = 0.0;
        double U = 0.0;

        void reset() { I = 0.0; U = 0.0; }
    };

    Coil(
        Winding primary,
        Winding secondary
    );


    void setCharging(bool isCharging);
    void step(double dt);

    void charge(double dt);
    double discharge(double dt, double Ubreak, double Rchain, double Ihold, double Uarc);

private:
    Winding primary_;
    Winding secondary_;
    double E_;
    double Ceq_;
    double k_;
    double M_;
    double n_;
    bool isCharging_;
};
