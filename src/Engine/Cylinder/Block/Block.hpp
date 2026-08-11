#pragma once
#include "Piston.hpp"
#include "Conrod.hpp"
#include "Crankshaft.hpp"

class Block {
public:
    Block(
        const Piston& piston,
        const Conrod& conrod,
        const Crankshaft& crankshaft
    );

    double get_bore() const { return piston.get_diameter(); }
    double get_stroke() const { return crankshaft.get_stroke(); }
    double get_bore_area() const;

    double get_piston_position(double crank_angle_deg) const;
    double get_piston_velocity(double crank_angle_deg, double rpm) const;

    double get_displaced_volume(double crank_angle_deg) const;
    double get_swept_volume() const;

private:
    const Piston& piston;
    const Conrod& conrod;
    const Crankshaft& crankshaft;
};
