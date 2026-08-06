#include "EngineFactory.h"
#include <stdexcept>

Engine EngineFactory::create_from_config(const ConfigReader& config) {
    Engine::Parameters params;

    // Geometry
    params.bore_mm = config.get_double("engine.bore_mm");
    params.stroke_mm = config.get_double("engine.stroke_mm");
    params.rod_length_mm = config.get_double("engine.rod_length_mm");
    params.chamber_volume_cc = config.get_double("engine.chamber_volume_cc");
    params.cylinder_count = config.get_int("engine.cylinder_count");

    // Physics (БЕЗ torque_scale!)
    params.friction_coefficient = config.get_double("engine.friction_coefficient");
    params.afr_stoich = config.get_double("engine.afr_stoich");
    params.k_polytropic = config.get_double("engine.k_polytropic");

    // Camshaft
    params.cam.intake_duration_deg = config.get_double("cam.intake_duration_deg");
    params.cam.exhaust_duration_deg = config.get_double("cam.exhaust_duration_deg");
    params.cam.intake_lift_mm = config.get_double("cam.intake_lift_mm");
    params.cam.exhaust_lift_mm = config.get_double_opt("cam.exhaust_lift_mm").value_or(params.cam.intake_lift_mm);
    params.cam.valve_diameter_intake_mm = config.get_double("cam.valve_diameter_intake_mm");
    params.cam.valve_diameter_exhaust_mm = config.get_double_opt("cam.valve_diameter_exhaust_mm").value_or(32.0);
    params.cam.overlap_deg = config.get_double("cam.overlap_deg");
    params.cam.lsa_deg = config.get_double_opt("cam.lsa_deg").value_or(108.0);

    // Intake
    params.intake.runner_length_mm = config.get_double("intake.runner_length_mm");
    params.intake.runner_diameter_mm = config.get_double("intake.runner_diameter_mm");

    // Carburetor (новое!)
    params.intake.primary_diffuser_mm = config.get_double_opt("intake.primary_diffuser_mm").value_or(23.0);
    params.intake.secondary_diffuser_mm = config.get_double_opt("intake.secondary_diffuser_mm").value_or(32.0);
    params.intake.primary_throat_mm = config.get_double_opt("intake.primary_throat_mm").value_or(32.0);
    params.intake.secondary_throat_mm = config.get_double_opt("intake.secondary_throat_mm").value_or(32.0);

    // Firing order
    auto order = config.get_double_array("engine.firing_order");
    if (order.empty()) {
        throw std::runtime_error("engine.firing_order is required");
    }
    params.firing_order = order;

    params.validate();

    Engine engine(params);
    return engine;
}
