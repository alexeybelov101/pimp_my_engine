#pragma once
#include <vector>
#include <string>
#include "Cylinder.h"

class Engine {
public:
    struct CamshaftParams {
        double intake_duration_deg = 232.0;
        double exhaust_duration_deg = 232.0;
        double intake_lift_mm = 9.728;
        double exhaust_lift_mm = 9.728;
        double overlap_deg = 12.0;
        double valve_diameter_intake_mm = 37.0;
        double valve_diameter_exhaust_mm = 32.0;
        double lsa_deg = 108.0;

        void validate() const;
    };

    struct IntakeParams {
        double runner_length_mm = 225.0;
        double runner_diameter_mm = 30.0;
        double throttle_diameter_mm = 32.0;

        // Параметры карбюратора (новое!)
        double primary_diffuser_mm = 23.0;    // Диффузор 1-й камеры
        double secondary_diffuser_mm = 32.0;  // Диффузор 2-й камеры
        double primary_throat_mm = 32.0;      // Диаметр 1-й камеры
        double secondary_throat_mm = 32.0;    // Диаметр 2-й камеры

        void validate() const;
    };

    struct Parameters {
        double bore_mm;
        double stroke_mm;
        double rod_length_mm;
        double chamber_volume_cc;
        int cylinder_count;
        double friction_coefficient;
        double afr_stoich;
        double k_polytropic;
        std::vector<double> firing_order;
        CamshaftParams cam;
        IntakeParams intake;

        void validate() const;
    };

    Engine() = default;
    explicit Engine(const Parameters& params);

    void set_parameters(const Parameters& p);
    void add_cylinder(const Cylinder& cyl);
    void set_rpm(double rpm);

    double calculate_torque(double throttle_pos = 1.0);
    double calculate_power(double torque, double rpm) const;

    double get_total_volume_liters() const;
    const Parameters& get_parameters() const { return params; }
    double get_rpm() const { return current_rpm; }
    int get_cylinder_count() const { return static_cast<int>(cylinders.size()); }

    // Для отладки
    double get_volumetric_efficiency(double rpm) const;
    double get_air_mass_per_intake(double ve) const;

private:
    Parameters params;
    std::vector<Cylinder> cylinders;
    double current_rpm = 0.0;

    double get_cylinder_volume_m3() const;
    double get_mechanical_efficiency(double rpm) const;
    double get_instant_torque(double crank_angle, double air_mass, double ve) const;
};
