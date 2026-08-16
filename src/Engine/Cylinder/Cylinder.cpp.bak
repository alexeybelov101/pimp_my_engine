#include "Cylinder.h"
#include <algorithm>
#include <stdexcept>

Cylinder::Cylinder(double bore, double stroke, double rod_length, double chamber_volume_cc)
    : bore_mm(bore), stroke_mm(stroke), rod_length_mm(rod_length),
      chamber_volume_cc(chamber_volume_cc) {
    if (bore <= 0 || stroke <= 0 || rod_length <= 0 || chamber_volume_cc <= 0) {
        throw std::invalid_argument("All cylinder parameters must be positive");
    }
}

double Cylinder::get_compression_ratio() const {
    double swept_volume = get_swept_volume();
    double chamber_volume_m3 = chamber_volume_cc * 1e-6;
    return (swept_volume + chamber_volume_m3) / chamber_volume_m3;
}

double Cylinder::get_swept_volume() const {
    double bore_m = bore_mm * 0.001;
    double stroke_m = stroke_mm * 0.001;
    return M_PI * pow(bore_m / 2.0, 2) * stroke_m;
}

double Cylinder::get_bore_area() const {
    double bore_m = bore_mm * 0.001;
    return M_PI * pow(bore_m / 2.0, 2);
}

double Cylinder::get_piston_position(double angle_deg) const {
    double theta = angle_deg * M_PI / 180.0;
    double R = (stroke_mm / 2.0) * 0.001;
    double L = rod_length_mm * 0.001;
    double ratio = R / L;

    if (ratio >= 1.0) {
        throw std::runtime_error("Invalid rod ratio: R/L >= 1");
    }

    double sin_theta = sin(theta);
    double cos_theta = cos(theta);
    double term = 1.0 - pow(ratio * sin_theta, 2.0);

    if (term < 0) term = 0;

    return R * (1.0 - cos_theta) + L * (1.0 - sqrt(term));
}

double Cylinder::get_volume(double angle_deg) const {
    double chamber_volume_m3 = chamber_volume_cc * 1e-6;
    double piston_pos_m = get_piston_position(angle_deg);
    double displaced_volume = get_bore_area() * piston_pos_m;
    return chamber_volume_m3 + displaced_volume;
}

double Cylinder::calculate_combustion_efficiency(double rpm) const {
    double efficiency = 0.95 - 0.00004 * rpm;
    return std::clamp(efficiency, 0.75, 0.95);
}

double Cylinder::calculate_lever_arm_factor(double angle_deg) const {
    double theta = angle_deg * M_PI / 180.0;
    double R = (stroke_mm / 2.0) * 0.001;
    double L = rod_length_mm * 0.001;
    double ratio = R / L;

    return sin(theta) * (1.0 + ratio * cos(theta));
}

double Cylinder::calculate_peak_pressure(const CombustionParams& params,
                                         double V_compression,
                                         double V_max) const {
    // ============================================
    // ТЕМПЕРАТУРА И ДАВЛЕНИЕ ВПУСКА
    // ============================================
    double T_intake = 300.0 + 0.01 * params.rpm;
    T_intake = std::clamp(T_intake, 300.0, 370.0);

    double p_intake = 98000.0;
    if (params.rpm > 3000) {
        p_intake -= 0.5 * (params.rpm - 3000);
    }
    p_intake = std::clamp(p_intake, 90000.0, 100000.0);

    // ============================================
    // ОСТАТОЧНЫЕ ГАЗЫ (зависят от перекрытия)
    // ============================================
    double residual_factor = 0.05;

    if (params.rpm < 2000) {
        double overlap_effect = 0.001 * (2000.0 - params.rpm) / 2000.0;
        residual_factor += overlap_effect;
    } else if (params.rpm > 5000) {
        residual_factor -= 0.001 * (params.rpm - 5000) / 3000.0;
    }
    residual_factor = std::clamp(residual_factor, 0.03, 0.08);

    // ============================================
    // ПЛОТНОСТЬ ВОЗДУХА
    // ============================================
    const double R_SPECIFIC_AIR = 287.0;
    double rho_air = p_intake / (R_SPECIFIC_AIR * T_intake);
    double effective_rho = rho_air * (1.0 - residual_factor);

    // ============================================
    // МАССА ВОЗДУХА
    // ============================================
    double air_mass = effective_rho * V_max * params.volumetric_efficiency;
    if (air_mass < 1e-9) air_mass = 1e-9;

    // ============================================
    // ТОПЛИВО
    // ============================================
    double stoich_fuel = air_mass / params.afr_stoich;
    double actual_fuel = std::min(params.fuel_mass_kg, stoich_fuel);
    double total_mass = air_mass + actual_fuel;

    // ============================================
    // СЖАТИЕ И СГОРАНИЕ
    // ============================================
    double compression_ratio = V_max / V_compression;
    const double GAMMA = 1.35;
    double T_compression = T_intake * pow(compression_ratio, GAMMA - 1.0);

    double combustion_efficiency = calculate_combustion_efficiency(params.rpm);

    const double LHV_GASOLINE = 44.0e6;
    double heat_released = actual_fuel * LHV_GASOLINE * combustion_efficiency;

    const double CV_AIR = 718.0;
    double T_combustion = T_compression + heat_released / (total_mass * CV_AIR);
    T_combustion = std::clamp(T_combustion, 1600.0, 2800.0);

    // ============================================
    // ДАВЛЕНИЕ
    // ============================================
    double pressure = (total_mass * R_SPECIFIC_AIR * T_combustion) / V_compression;

    // Фаза сгорания (пик после ВМТ)
    pressure *= 0.85;

    return std::clamp(pressure, 15e5, 100e5);
}

double Cylinder::calculate_torque(const CombustionParams& params,
                                  double angle_deg) const {
    if (angle_deg < 0.0 || angle_deg > 180.0) return 0.0;

    double V = get_volume(angle_deg);
    double V_max = get_volume(180.0);
    double V_compression = get_volume(0.0);

    double P_max = calculate_peak_pressure(params, V_compression, V_max);

    double pressure = P_max * pow(V_compression / V, params.k_polytropic);

    const double EXHAUST_PRESSURE = 105000.0;
    pressure = std::max(pressure, EXHAUST_PRESSURE);

    const double ATMOSPHERIC = 101325.0;
    double effective_pressure = pressure - ATMOSPHERIC;
    if (effective_pressure < 0) return 0.0;

    double force = effective_pressure * get_bore_area();

    double R = (stroke_mm / 2.0) * 0.001;
    double lever_factor = calculate_lever_arm_factor(angle_deg);
    double torque = force * R * lever_factor;

    return std::max(0.0, torque);
}
