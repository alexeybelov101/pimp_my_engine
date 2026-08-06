#include "Engine.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <numeric>

// ==================== Validation ====================

void Engine::CamshaftParams::validate() const {
    if (intake_duration_deg <= 0 || exhaust_duration_deg <= 0) {
        throw std::invalid_argument("Cam duration must be positive");
    }
    if (intake_lift_mm <= 0 || exhaust_lift_mm <= 0) {
        throw std::invalid_argument("Cam lift must be positive");
    }
    if (overlap_deg < 0 || overlap_deg > 180) {
        throw std::invalid_argument("Overlap must be between 0 and 180");
    }
    if (lsa_deg < 80 || lsa_deg > 130) {
        throw std::invalid_argument("LSA must be between 80 and 130");
    }
}

void Engine::IntakeParams::validate() const {
    if (runner_length_mm <= 0 || runner_diameter_mm <= 0) {
        throw std::invalid_argument("Intake runner dimensions must be positive");
    }
    if (throttle_diameter_mm <= 0) {
        throw std::invalid_argument("Throttle diameter must be positive");
    }
    if (primary_diffuser_mm <= 0 || secondary_diffuser_mm <= 0) {
        throw std::invalid_argument("Diffuser diameters must be positive");
    }
    if (primary_diffuser_mm > primary_throat_mm) {
        throw std::invalid_argument("Diffuser cannot be larger than throat");
    }
}

void Engine::Parameters::validate() const {
    if (bore_mm <= 0 || stroke_mm <= 0 || rod_length_mm <= 0) {
        throw std::invalid_argument("Engine geometry must be positive");
    }
    if (chamber_volume_cc <= 0) {
        throw std::invalid_argument("Chamber volume must be positive");
    }
    if (cylinder_count <= 0) {
        throw std::invalid_argument("Cylinder count must be positive");
    }
    if (friction_coefficient < 0 || friction_coefficient > 1) {
        throw std::invalid_argument("Friction coefficient must be between 0 and 1");
    }
    if (afr_stoich <= 0) {
        throw std::invalid_argument("AFR must be positive");
    }
    if (k_polytropic < 1.0 || k_polytropic > 1.5) {
        throw std::invalid_argument("Polytropic index must be between 1.0 and 1.5");
    }
    if (firing_order.empty()) {
        throw std::invalid_argument("Firing order must not be empty");
    }
    cam.validate();
    intake.validate();
}

// ==================== Engine Implementation ====================

Engine::Engine(const Parameters& p) {
    set_parameters(p);
}

void Engine::set_parameters(const Parameters& p) {
    p.validate();
    params = p;
    cylinders.clear();

    Cylinder cyl(params.bore_mm, params.stroke_mm,
                 params.rod_length_mm, params.chamber_volume_cc);

    for (int i = 0; i < params.cylinder_count; ++i) {
        cylinders.push_back(cyl);
    }
}

void Engine::add_cylinder(const Cylinder& cyl) {
    cylinders.push_back(cyl);
}

void Engine::set_rpm(double rpm) {
    if (rpm < 0) {
        throw std::invalid_argument("RPM cannot be negative");
    }
    current_rpm = rpm;
}

double Engine::get_cylinder_volume_m3() const {
    if (cylinders.empty()) {
        double bore_m = params.bore_mm * 0.001;
        double stroke_m = params.stroke_mm * 0.001;
        return M_PI * pow(bore_m / 2.0, 2) * stroke_m;
    }
    return cylinders[0].get_swept_volume();
}

double Engine::get_total_volume_liters() const {
    double cyl_volume = get_cylinder_volume_m3();
    return cyl_volume * 1000.0 * cylinders.size();
}

double Engine::get_mechanical_efficiency(double rpm) const {
    double efficiency = 1.0 - params.friction_coefficient * (rpm / 1500.0);
    return std::clamp(efficiency, 0.65, 0.95);
}

double Engine::get_volumetric_efficiency(double rpm) const {
    const auto& cam = params.cam;
    const auto& intake = params.intake;

    // ============================================
    // ГЕОМЕТРИЯ ДВИГАТЕЛЯ
    // ============================================
    double bore_m = params.bore_mm * 0.001;
    double stroke_m = params.stroke_mm * 0.001;
    double lift_m = cam.intake_lift_mm * 0.001;
    double valve_dia_m = cam.valve_diameter_intake_mm * 0.001;

    double piston_area = M_PI * pow(bore_m / 2.0, 2);
    double valve_area = M_PI * valve_dia_m * lift_m * 0.7;
    double cylinder_volume = piston_area * stroke_m;

    // ============================================
    // КАРБЮРАТОР - ОГРАНИЧЕНИЕ ПОТОКА (новое!)
    // ============================================
    // Площадь диффузоров карбюратора
    double primary_diffuser_area = M_PI * pow(intake.primary_diffuser_mm * 0.001 / 2.0, 2);
    double secondary_diffuser_area = M_PI * pow(intake.secondary_diffuser_mm * 0.001 / 2.0, 2);

    // Суммарная площадь диффузоров
    double total_diffuser_area = primary_diffuser_area + secondary_diffuser_area;

    // ============================================
    // СКОРОСТЬ ПОТОКА В ДИФФУЗОРАХ (новое!)
    // ============================================
    // Объемный расход воздуха через двигатель
    double engine_flow = cylinder_volume * (rpm / 60.0) / 2.0; // м³/с (для 4-тактного /2)

    // Скорость в диффузоре (м/с)
    double diffuser_velocity = engine_flow / total_diffuser_area;

    // Максимальная скорость в диффузоре (для карбюратора)
    // При скорости > 50 м/с начинаются большие потери
    // При скорости > 80 м/с - критические потери
    double max_diffuser_velocity = 50.0; // м/с

    // Коэффициент потерь в диффузоре (зависит от скорости)
    double diffuser_loss = 1.0;
    if (diffuser_velocity > max_diffuser_velocity) {
        double excess = diffuser_velocity - max_diffuser_velocity;
        // Потери растут квадратично
        diffuser_loss = 1.0 - 0.01 * pow(excess / 10.0, 2);
    }
    diffuser_loss = std::clamp(diffuser_loss, 0.30, 1.0);

    // ============================================
    // БАЗОВЫЙ VE (через клапан)
    // ============================================
    double mean_piston_speed = 2.0 * stroke_m * (rpm / 60.0);
    double flow_velocity = mean_piston_speed * (piston_area / valve_area);
    flow_velocity = std::min(flow_velocity, 110.0);

    double time_open = (cam.intake_duration_deg / 360.0) * (60.0 / rpm);
    double air_volume = valve_area * flow_velocity * time_open;
    double base_ve = air_volume / cylinder_volume;

    // ============================================
    // КОРРЕКЦИЯ: ДРОССЕЛЬНАЯ ЗАСЛОНКА
    // ============================================
    double throttle_correction;
    if (rpm < 1000) {
        throttle_correction = 0.30 + 0.0002 * rpm;
    } else if (rpm < 2000) {
        throttle_correction = 0.50 + 0.00015 * (rpm - 1000);
    } else {
        throttle_correction = 0.65 + 0.00005 * (rpm - 2000);
    }
    throttle_correction = std::clamp(throttle_correction, 0.30, 0.95);

    // ============================================
    // КОРРЕКЦИЯ: ПУЛЬСАЦИИ
    // ============================================
    double length_m = std::max(intake.runner_length_mm * 0.001, 0.01);
    const double SPEED_OF_SOUND = 343.0;
    double resonant_rpm = (SPEED_OF_SOUND / (4.0 * length_m)) * 60.0;

    double pulsation_factor;
    if (rpm < resonant_rpm * 0.5) {
        pulsation_factor = 0.85 + 0.10 * (rpm / (resonant_rpm * 0.5));
    } else if (rpm < resonant_rpm * 0.8) {
        pulsation_factor = 0.95 + 0.05 * ((rpm - resonant_rpm * 0.5) / (resonant_rpm * 0.3));
    } else if (rpm < resonant_rpm * 1.2) {
        double center = resonant_rpm;
        double width = resonant_rpm * 0.2;
        pulsation_factor = 1.0 + 0.15 * exp(-pow((rpm - center) / width, 2));
    } else {
        pulsation_factor = 0.85 - 0.10 * ((rpm - resonant_rpm * 1.2) / (resonant_rpm * 0.5));
    }
    pulsation_factor = std::clamp(pulsation_factor, 0.75, 1.15);

    // ============================================
    // КОРРЕКЦИЯ: ТЕПЛООБМЕН
    // ============================================
    double heat_transfer_factor;
    if (rpm < 1500) {
        heat_transfer_factor = 0.90 + 0.00005 * rpm;
    } else if (rpm < 3000) {
        heat_transfer_factor = 0.975 + 0.00001 * (rpm - 1500);
    } else {
        heat_transfer_factor = 0.99;
    }
    heat_transfer_factor = std::clamp(heat_transfer_factor, 0.90, 0.99);

    // ============================================
    // КОРРЕКЦИЯ: ПЕРЕКРЫТИЕ
    // ============================================
    double overlap = cam.overlap_deg;
    double overlap_effect;
    if (rpm < 1500) {
        overlap_effect = -0.04 * (overlap / 10.0) * (1500.0 - rpm) / 1500.0;
    } else if (rpm < 3000) {
        overlap_effect = -0.02 * (overlap / 10.0) * (3000.0 - rpm) / 1500.0;
    } else if (rpm < 4500) {
        overlap_effect = 0.02 * (overlap / 10.0) * (rpm - 3000.0) / 1500.0;
    } else if (rpm < 6000) {
        double peak = 0.02 * (overlap / 10.0);
        overlap_effect = peak * (1.0 - (rpm - 4500.0) / 1500.0);
    } else {
        overlap_effect = 0.0;
    }
    overlap_effect = std::clamp(overlap_effect, -0.08, 0.06);

    // ============================================
    // КОРРЕКЦИЯ: ИНЕРЦИОННОСТЬ
    // ============================================
    double inertia_factor;
    if (rpm < 1000) {
        inertia_factor = 0.70 + 0.0002 * rpm;
    } else if (rpm < 2000) {
        inertia_factor = 0.90 + 0.00005 * (rpm - 1000);
    } else {
        inertia_factor = 0.95;
    }
    inertia_factor = std::clamp(inertia_factor, 0.70, 0.95);

    // ============================================
    // ИТОГОВЫЙ VE
    // ============================================
    double final_ve = base_ve
                     * throttle_correction
                     * pulsation_factor
                     * heat_transfer_factor
                     * (1.0 + overlap_effect)
                     * inertia_factor
                     * diffuser_loss;  // <-- Ограничение карбюратора!

    return std::clamp(final_ve, 0.20, 0.98);
}

double Engine::get_air_mass_per_intake(double ve) const {
    double cylinder_volume = get_cylinder_volume_m3();

    double rho_air = 1.22 - 0.000035 * current_rpm;
    rho_air = std::clamp(rho_air, 0.90, 1.22);

    return cylinder_volume * ve * rho_air;
}

double Engine::get_instant_torque(double crank_angle, double air_mass, double ve) const {
    double total_torque = 0.0;
    double fuel_mass = air_mass / params.afr_stoich;

    for (size_t i = 0; i < cylinders.size(); ++i) {
        size_t idx = i % params.firing_order.size();
        double offset = params.firing_order[idx];
        double cyl_angle = crank_angle - offset;

        cyl_angle = fmod(cyl_angle, 720.0);
        if (cyl_angle < 0) cyl_angle += 720.0;

        if (cyl_angle >= 0.0 && cyl_angle <= 180.0) {
            Cylinder::CombustionParams cyl_params{
                current_rpm,
                ve,
                fuel_mass,
                air_mass,
                params.afr_stoich,
                params.k_polytropic
            };

            total_torque += cylinders[i].calculate_torque(cyl_params, cyl_angle);
        }
    }

    return total_torque;
}

double Engine::calculate_torque(double throttle_pos) {
    if (cylinders.empty()) return 0.0;

    throttle_pos = std::clamp(throttle_pos, 0.0, 1.0);

    double ve = get_volumetric_efficiency(current_rpm);
    double air_mass = get_air_mass_per_intake(ve) * throttle_pos;

    const int steps = 720;
    double total_torque_sum = 0.0;

    for (int step = 0; step < steps; ++step) {
        double crank_angle = step * (720.0 / steps);
        total_torque_sum += get_instant_torque(crank_angle, air_mass, ve);
    }

    double avg_indicated_torque = total_torque_sum / steps;

    double mechanical_efficiency = get_mechanical_efficiency(current_rpm);
    double effective_torque = avg_indicated_torque * mechanical_efficiency;

    return std::max(0.0, effective_torque);
}

double Engine::calculate_power(double torque, double rpm) const {
    double omega = rpm * 2.0 * M_PI / 60.0;
    return torque * omega;
}
