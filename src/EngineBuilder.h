#pragma once
#include "Engine.h"
#include "valvetrain/Valvetrain.h"
#include "cranktrain/Cranktrain.h"
#include "systems/FuelSystem.h"
#include <memory>
#include <vector>

/**
 * @brief Fluent-интерфейс для сборки двигателя из компонентов
 * 
 * Пример использования:
 * @code
 * EngineBuilder builder;
 * auto engine = builder
 *     .set_bore_mm(79.0)
 *     .set_stroke_mm(66.0)
 *     .set_rod_length_mm(126.0)
 *     .set_chamber_volume_cc(43.1)
 *     .set_cylinder_count(4)
 *     .set_cam_duration_deg(232.0)
 *     .set_cam_lift_mm(9.728)
 *     .set_valve_diameter_mm(37.0, 32.0)
 *     .set_overlap_deg(12.0)
 *     .set_lsa_deg(108.0)
 *     .set_intake_runner_mm(230.0, 30.0)
 *     .set_carburetor_diffusers_mm(23.0, 32.0)
 *     .set_firing_order({0, 180, 360, 540})
 *     .set_friction_coefficient(0.08)
 *     .set_afr_stoich(14.7)
 *     .set_k_polytropic(1.27)
 *     .build();
 * @endcode
 */
class EngineBuilder {
public:
    EngineBuilder() = default;

    // === Геометрия двигателя ===
    EngineBuilder& set_bore_mm(double bore) {
        params_.bore_mm = bore;
        return *this;
    }

    EngineBuilder& set_stroke_mm(double stroke) {
        params_.stroke_mm = stroke;
        return *this;
    }

    EngineBuilder& set_rod_length_mm(double rod_length) {
        params_.rod_length_mm = rod_length;
        return *this;
    }

    EngineBuilder& set_chamber_volume_cc(double volume) {
        params_.chamber_volume_cc = volume;
        return *this;
    }

    EngineBuilder& set_cylinder_count(int count) {
        params_.cylinder_count = count;
        return *this;
    }

    // === Физические параметры ===
    EngineBuilder& set_friction_coefficient(double coeff) {
        params_.friction_coefficient = coeff;
        return *this;
    }

    EngineBuilder& set_afr_stoich(double afr) {
        params_.afr_stoich = afr;
        return *this;
    }

    EngineBuilder& set_k_polytropic(double k) {
        params_.k_polytropic = k;
        return *this;
    }

    // === ГРМ (Camshaft) ===
    EngineBuilder& set_cam_duration_deg(double intake, double exhaust) {
        params_.cam.intake_duration_deg = intake;
        params_.cam.exhaust_duration_deg = exhaust;
        return *this;
    }

    EngineBuilder& set_cam_duration_deg(double duration) {
        return set_cam_duration_deg(duration, duration);
    }

    EngineBuilder& set_cam_lift_mm(double intake, double exhaust) {
        params_.cam.intake_lift_mm = intake;
        params_.cam.exhaust_lift_mm = exhaust;
        return *this;
    }

    EngineBuilder& set_cam_lift_mm(double lift) {
        return set_cam_lift_mm(lift, lift);
    }

    EngineBuilder& set_valve_diameter_mm(double intake, double exhaust) {
        params_.cam.valve_diameter_intake_mm = intake;
        params_.cam.valve_diameter_exhaust_mm = exhaust;
        return *this;
    }

    EngineBuilder& set_valve_diameter_mm(double diameter) {
        return set_valve_diameter_mm(diameter, diameter);
    }

    EngineBuilder& set_overlap_deg(double overlap) {
        params_.cam.overlap_deg = overlap;
        return *this;
    }

    EngineBuilder& set_lsa_deg(double lsa) {
        params_.cam.lsa_deg = lsa;
        return *this;
    }

    // === Впускная система ===
    EngineBuilder& set_intake_runner_mm(double length, double diameter) {
        params_.intake.runner_length_mm = length;
        params_.intake.runner_diameter_mm = diameter;
        return *this;
    }

    EngineBuilder& set_throttle_diameter_mm(double diameter) {
        params_.intake.throttle_diameter_mm = diameter;
        return *this;
    }

    // === Карбюратор ===
    EngineBuilder& set_carburetor_diffusers_mm(double primary, double secondary) {
        params_.intake.primary_diffuser_mm = primary;
        params_.intake.secondary_diffuser_mm = secondary;
        return *this;
    }

    EngineBuilder& set_carburetor_throats_mm(double primary, double secondary) {
        params_.intake.primary_throat_mm = primary;
        params_.intake.secondary_throat_mm = secondary;
        return *this;
    }

    // === Порядок зажигания ===
    EngineBuilder& set_firing_order(const std::vector<double>& order) {
        params_.firing_order = order;
        return *this;
    }

    /**
     * @brief Построение двигателя
     * @throws std::invalid_argument при некорректных параметрах
     */
    Engine build() const {
        params_.validate();
        return Engine(params_);
    }

    /**
     * @brief Построение с возвратом shared_ptr
     */
    std::shared_ptr<Engine> build_shared() const {
        return std::make_shared<Engine>(build());
    }

    /**
     * @brief Получение текущих параметров (для инспекции)
     */
    const Engine::Parameters& get_parameters() const {
        return params_;
    }

private:
    Engine::Parameters params_;
};
