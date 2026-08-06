#pragma once
#include <cmath>

class Cylinder {
public:
    Cylinder(double bore, double stroke, double rod_length, double chamber_volume_cc);

    double get_bore() const { return bore_mm; }
    double get_stroke() const { return stroke_mm; }
    double get_rod_length() const { return rod_length_mm; }
    double get_chamber_volume() const { return chamber_volume_cc; }

    double get_compression_ratio() const;
    double get_piston_position(double angle_deg) const;
    double get_volume(double angle_deg) const;
    double get_swept_volume() const;
    double get_bore_area() const;

    struct CombustionParams {
        double rpm;
        double volumetric_efficiency;
        double fuel_mass_kg;
        double air_mass_kg;
        double afr_stoich;
        double k_polytropic;
    };

    double calculate_torque(const CombustionParams& params, double angle_deg) const;

private:
    double bore_mm;
    double stroke_mm;
    double rod_length_mm;
    double chamber_volume_cc;

    double calculate_peak_pressure(const CombustionParams& params,
                                   double V_compression,
                                   double V_max) const;
    double calculate_combustion_efficiency(double rpm) const;
    double calculate_lever_arm_factor(double angle_deg) const;
};
