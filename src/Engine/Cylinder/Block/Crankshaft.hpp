#pragma once
#include <cmath>

class Crankshaft {
public:
    explicit Crankshaft(double stroke_mm);

    double get_stroke() const { return stroke_mm; }
    double get_crank_radius() const { return stroke_mm / 2.0; }

    // Высота подъема кривошипа для заданного угла
    double get_crank_height(double crank_angle_deg) const;

private:
    double stroke_mm;
};
