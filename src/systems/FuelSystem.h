#pragma once
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace systems {

/**
 * @brief Система топливоподачи
 * Рассчитывает массу топлива на основе положения дросселя и Lambda
 */
class FuelSystem {
public:
    FuelSystem() = default;

    FuelSystem(double afr_stoich, double injector_flow_rate_cc_min = 200.0)
        : afr_stoich_(afr_stoich)
        , injector_flow_rate_cc_min_(injector_flow_rate_cc_min) {
        validate();
    }

    double afr_stoich() const { return afr_stoich_; }
    double injector_flow_rate_cc_min() const { return injector_flow_rate_cc_min_; }

    /**
     * @brief Расчет массы топлива для заданной массы воздуха
     * @param air_mass_kg Масса воздуха (кг)
     * @param lambda Коэффициент избытка воздуха (1.0 = стехиометрия)
     * @return Масса топлива (кг)
     */
    double calculate_fuel_mass(double air_mass_kg, double lambda = 1.0) const {
        if (air_mass_kg <= 0) {
            return 0.0;
        }

        // AFR_actual = AFR_stoich * lambda
        double afr_actual = afr_stoich_ * lambda;

        return air_mass_kg / afr_actual;
    }

    /**
     * @brief Расчет требуемого времени впрыска (мс)
     * @param fuel_mass_kg Требуемая масса топлива
     * @param engine_rpm Обороты двигателя
     * @return Длительность импульса впрыска (мс)
     */
    double calculate_injection_duration_ms(double fuel_mass_kg, double engine_rpm) const {
        if (fuel_mass_kg <= 0 || engine_rpm <= 0) {
            return 0.0;
        }

        // Перевод расхода из cc/min в кг/с (плотность бензина ~0.74 кг/л)
        const double FUEL_DENSITY_KG_L = 0.74;
        double flow_rate_kg_s = (injector_flow_rate_cc_min_ * 1e-3) * 
                                FUEL_DENSITY_KG_L / 60.0;

        // Время впрыска (с)
        double duration_s = fuel_mass_kg / flow_rate_kg_s;

        // Ограничение максимального времени впрыска (не более 80% такта впуска)
        double max_duration_s = 0.8 * (60.0 / engine_rpm) / 2.0; // 4-тактный

        return std::min(duration_s * 1000.0, max_duration_s * 1000.0);
    }

    /**
     * @brief Получение Lambda по желаемому AFR
     */
    double get_lambda_from_afr(double afr_target) const {
        if (afr_target <= 0) {
            return 1.0;
        }
        return afr_target / afr_stoich_;
    }

    /**
     * @brief Получение AFR по Lambda
     */
    double get_afr_from_lambda(double lambda) const {
        return afr_stoich_ * lambda;
    }

private:
    double afr_stoich_ = 14.7;
    double injector_flow_rate_cc_min_ = 200.0;

    void validate() const {
        if (afr_stoich_ <= 0) {
            throw std::invalid_argument("FuelSystem: AFR must be positive");
        }
        if (injector_flow_rate_cc_min_ <= 0) {
            throw std::invalid_argument("FuelSystem: injector flow rate must be positive");
        }
    }
};


/**
 * @brief Впускной патрубок (заготовка для индивидуальных патрубков)
 */
class IntakeRunner {
public:
    IntakeRunner() = default;

    IntakeRunner(double length_mm, double diameter_mm)
        : length_mm_(length_mm)
        , diameter_mm_(diameter_mm) {
        validate();
    }

    double length_mm() const { return length_mm_; }
    double diameter_mm() const { return diameter_mm_; }

    /**
     * @brief Площадь поперечного сечения (мм²)
     */
    double cross_section_area_mm2() const {
        return M_PI * std::pow(diameter_mm_ / 2.0, 2);
    }

    /**
     * @brief Объем патрубка (см³)
     */
    double volume_cc() const {
        double area_m2 = cross_section_area_mm2() * 1e-6;
        double length_m = length_mm_ * 0.001;
        return area_m2 * length_m * 1e6;
    }

    /**
     * @brief Резонансные обороты (упрощенно)
     * f = c / (4 * L), где c - скорость звука
     */
    double resonant_rpm() const {
        const double SPEED_OF_SOUND_MS = 343.0;
        double length_m = length_mm_ * 0.001;
        
        // Частота резонанса (Гц)
        double freq_hz = SPEED_OF_SOUND_MS / (4.0 * length_m);
        
        // Перевод в RPM (для 4-тактного двигателя)
        return freq_hz * 60.0 / 2.0;
    }

private:
    double length_mm_ = 0.0;
    double diameter_mm_ = 0.0;

    void validate() const {
        if (length_mm_ <= 0 || diameter_mm_ <= 0) {
            throw std::invalid_argument("IntakeRunner: dimensions must be positive");
        }
    }
};


/**
 * @brief Выпускной патрубок (заготовка для индивидуальных патрубков)
 */
class ExhaustRunner {
public:
    ExhaustRunner() = default;

    ExhaustRunner(double length_mm, double diameter_mm)
        : length_mm_(length_mm)
        , diameter_mm_(diameter_mm) {
        validate();
    }

    double length_mm() const { return length_mm_; }
    double diameter_mm() const { return diameter_mm_; }

    /**
     * @brief Площадь поперечного сечения (мм²)
     */
    double cross_section_area_mm2() const {
        return M_PI * std::pow(diameter_mm_ / 2.0, 2);
    }

    /**
     * @brief Объем патрубка (см³)
     */
    double volume_cc() const {
        double area_m2 = cross_section_area_mm2() * 1e-6;
        double length_m = length_mm_ * 0.001;
        return area_m2 * length_m * 1e6;
    }

private:
    double length_mm_ = 0.0;
    double diameter_mm_ = 0.0;

    void validate() const {
        if (length_mm_ <= 0 || diameter_mm_ <= 0) {
            throw std::invalid_argument("ExhaustRunner: dimensions must be positive");
        }
    }
};

} // namespace systems
