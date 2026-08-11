#include "EngineFactory.h"
#include "ConfigReader.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <chrono>

int main(int argc, char* argv[]) {
    std::cout << "=== Pimp My 21011 - Console Dyno Stand ===" << std::endl;
    std::cout << "Version: 3.0 (Without torque_scale, with overlap)" << std::endl;

    try {
        ConfigReader config;
        std::string config_file = (argc > 1) ? argv[1] : "config.cfg";

        if (!config.load(config_file)) {
            std::cerr << "FATAL: Cannot load config file: " << config_file << std::endl;
            return 1;
        }

        Engine engine = EngineFactory::create_from_config(config);

        const auto& params = engine.get_parameters();
        double total_volume = engine.get_total_volume_liters();

        std::cout << "\nEngine Configuration:" << std::endl;
        std::cout << "  Type: " << params.cylinder_count << "-cylinder inline" << std::endl;
        std::cout << "  Bore: " << params.bore_mm << " mm" << std::endl;
        std::cout << "  Stroke: " << params.stroke_mm << " mm" << std::endl;
        std::cout << "  Total volume: " << std::fixed << std::setprecision(3)
                  << total_volume << " L" << std::endl;
        std::cout << "  Friction coefficient: " << params.friction_coefficient << std::endl;
        std::cout << "  Overlap: " << params.cam.overlap_deg << " deg" << std::endl;
        std::cout << "  LSA: " << params.cam.lsa_deg << " deg" << std::endl;

        std::cout << "\nRPM\t Torque(Nm)\t Power(hp)\t VE\t Air(g)" << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;

        double max_torque = 0;
        double max_power = 0;
        int max_torque_rpm = 0;
        int max_power_rpm = 0;

        int rpm_start = config.get_int("test.rpm_start");
        int rpm_end = config.get_int("test.rpm_end");
        int rpm_step = config.get_int("test.rpm_step");

        for (int rpm = rpm_start; rpm <= rpm_end; rpm += rpm_step) {
            engine.set_rpm(rpm);
            double torque = engine.calculate_torque(1.0);
            double power = engine.calculate_power(torque, rpm) / 745.7;

            double ve = engine.get_volumetric_efficiency(rpm);
            double air_mass = engine.get_air_mass_per_intake(ve) * 1000; // в граммах

            if (torque > max_torque) {
                max_torque = torque;
                max_torque_rpm = rpm;
            }
            if (power > max_power) {
                max_power = power;
                max_power_rpm = rpm;
            }

            // if (rpm % 500 == 0 || rpm == rpm_start || rpm == rpm_end ||
            //     rpm == 3400 || rpm == 5600) {
                std::cout << rpm << "\t "
                          << std::fixed << std::setprecision(1) << torque << "\t\t "
                          << std::setprecision(1) << power << "\t\t "
                          << std::setprecision(3) << ve << "\t "
                          << std::setprecision(2) << air_mass;

                if (rpm == 3400) std::cout << "  *** TARGET: 94 Nm ***";
                if (rpm == 5600) std::cout << "  *** TARGET: 69 hp ***";
                std::cout << std::endl;
            // }
        }

        std::cout << "\n=== Results ===" << std::endl;
        std::cout << "Max Torque: " << std::fixed << std::setprecision(1)
                  << max_torque << " Nm at " << max_torque_rpm << " RPM" << std::endl;
        std::cout << "Max Power: " << std::setprecision(1)
                  << max_power << " hp at " << max_power_rpm << " RPM" << std::endl;

        double error_torque = std::abs(max_torque - 94.0) / 94.0 * 100;
        double error_power = std::abs(max_power - 69.0) / 69.0 * 100;

        std::cout << "\n=== Comparison with Factory Specs ===" << std::endl;
        std::cout << "Factory:  69 hp @ 5600 RPM, 94 Nm @ 3400 RPM" << std::endl;
        std::cout << "Error: " << std::fixed << std::setprecision(1)
                  << error_torque << "% (torque), "
                  << error_power << "% (power)" << std::endl;

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
}
