#pragma once
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace cranktrain {

/**
 * @brief Геометрия цилиндра и поршневой группы
 */
class Block {
public:
    Block() = default;

    Block(double bore_mm, 
          double stroke_mm, 
          double rod_length_mm,
          double chamber_volume_cc)
        : bore_mm_(bore_mm)
        , stroke_mm_(stroke_mm)
        , rod_length_mm_(rod_length_mm)
        , chamber_volume_cc_(chamber_volume_cc) {
        validate();
    }

    double bore_mm() const { return bore_mm_; }
    double stroke_mm() const { return stroke_mm_; }
    double rod_length_mm() const { return rod_length_mm_; }
    double chamber_volume_cc() const { return chamber_volume_cc_; }

    /**
     * @brief Площадь поршня (мм²)
     */
    double bore_area_mm2() const {
        return M_PI * std::pow(bore_mm_ / 2.0, 2);
    }

    /**
     * @brief Рабочий объем цилиндра (м³)
     */
    double swept_volume_m3() const {
        double bore_m = bore_mm_ * 0.001;
        double stroke_m = stroke_mm_ * 0.001;
        return M_PI * std::pow(bore_m / 2.0, 2) * stroke_m;
    }

    /**
     * @brief Рабочий объем в см³ (cc)
     */
    double swept_volume_cc() const {
        return swept_volume_m3() * 1e6;
    }

    /**
     * @brief Степень сжатия
     */
    double compression_ratio() const {
        double swept = swept_volume_m3();
        double chamber = chamber_volume_cc_ * 1e-6;
        return (swept + chamber) / chamber;
    }

    /**
     * @brief Положение поршня от ВМТ (мм)
     * @param angle_deg Угол поворота коленвала (0 = ВМТ)
     */
    double piston_position_mm(double angle_deg) const {
        double theta = angle_deg * M_PI / 180.0;
        double R = (stroke_mm_ / 2.0) * 0.001;  // радиус кривошипа (м)
        double L = rod_length_mm_ * 0.001;       // длина шатуна (м)
        double ratio = R / L;

        if (ratio >= 1.0) {
            throw std::runtime_error("Invalid rod ratio: R/L >= 1");
        }

        double sin_theta = std::sin(theta);
        double cos_theta = std::cos(theta);
        double term = 1.0 - std::pow(ratio * sin_theta, 2.0);

        if (term < 0) term = 0;

        return (R * (1.0 - cos_theta) + L * (1.0 - std::sqrt(term))) * 1000.0; // в мм
    }

    /**
     * @brief Объем камеры сгорания при заданном угле (м³)
     */
    double volume_at_angle_m3(double angle_deg) const {
        double chamber_m3 = chamber_volume_cc_ * 1e-6;
        double piston_pos_m = piston_position_mm(angle_deg) * 0.001;
        double displaced = bore_area_mm2() * 1e-6 * piston_pos_m;
        return chamber_m3 + displaced;
    }

    /**
     * @brief Скорость поршня (м/с)
     */
    double piston_velocity_ms(double angle_deg, double rpm) const {
        double omega = rpm * 2.0 * M_PI / 60.0;
        double R = (stroke_mm_ / 2.0) * 0.001;
        double L = rod_length_mm_ * 0.001;
        double ratio = R / L;

        double theta = angle_deg * M_PI / 180.0;
        double sin_theta = std::sin(theta);
        double cos_theta = std::cos(theta);

        // Приближенная формула скорости поршня
        double v = omega * R * (sin_theta + ratio * sin_theta * cos_theta / 
                                std::sqrt(1.0 - std::pow(ratio * sin_theta, 2)));

        return std::abs(v);
    }

    /**
     * @brief Средняя скорость поршня (м/с)
     */
    double mean_piston_speed_ms(double rpm) const {
        double stroke_m = stroke_mm_ * 0.001;
        return 2.0 * stroke_m * (rpm / 60.0);
    }

private:
    double bore_mm_ = 0.0;
    double stroke_mm_ = 0.0;
    double rod_length_mm_ = 0.0;
    double chamber_volume_cc_ = 0.0;

    void validate() const {
        if (bore_mm_ <= 0 || stroke_mm_ <= 0 || rod_length_mm_ <= 0) {
            throw std::invalid_argument("Block: dimensions must be positive");
        }
        if (chamber_volume_cc_ <= 0) {
            throw std::invalid_argument("Block: chamber volume must be positive");
        }
    }
};


/**
 * @brief Коленчатый вал
 */
class Crankshaft {
public:
    Crankshaft() = default;

    explicit Crankshaft(int cylinder_count)
        : cylinder_count_(cylinder_count) {}

    int cylinder_count() const { return cylinder_count_; }

    /**
     * @brief Установка порядка работы цилиндров
     * @param firing_order Углы зажигания для каждого цилиндра
     */
    void set_firing_order(const std::vector<double>& firing_order) {
        if (firing_order.empty()) {
            throw std::invalid_argument("Crankshaft: firing order cannot be empty");
        }
        firing_order_ = firing_order;
    }

    /**
     * @brief Получение угла зажигания для цилиндра
     */
    double get_cylinder_offset(int cylinder_index) const {
        if (firing_order_.empty()) {
            return cylinder_index * 720.0 / cylinder_count_;
        }
        return firing_order_[cylinder_index % firing_order_.size()];
    }

    /**
     * @brief Текущий угол поворота коленвала
     */
    void set_angle_deg(double angle) {
        current_angle_deg_ = std::fmod(angle, 720.0);
        if (current_angle_deg_ < 0) {
            current_angle_deg_ += 720.0;
        }
    }

    double current_angle_deg() const { return current_angle_deg_; }

    /**
     * @brief Угловая скорость (рад/с)
     */
    void set_angular_velocity_rad_s(double omega) {
        angular_velocity_rad_s_ = omega;
    }

    double angular_velocity_rad_s() const { return angular_velocity_rad_s_; }

    /**
     * @brief Обороты двигателя (RPM)
     */
    double rpm() const {
        return angular_velocity_rad_s_ * 60.0 / (2.0 * M_PI);
    }

    void set_rpm(double rpm) {
        angular_velocity_rad_s_ = rpm * 2.0 * M_PI / 60.0;
    }

private:
    int cylinder_count_ = 0;
    std::vector<double> firing_order_;
    double current_angle_deg_ = 0.0;
    double angular_velocity_rad_s_ = 0.0;
};


/**
 * @brief Маховик - инерционный элемент
 */
class Flywheel {
public:
    Flywheel() = default;

    /**
     * @brief Создание маховика с автоматическим расчетом момента инерции
     * @param mass_kg Масса маховика
     * @param radius_mm Радиус маховика
     */
    Flywheel(double mass_kg, double radius_mm)
        : mass_kg_(mass_kg)
        , radius_mm_(radius_mm)
        , inertia_kg_m2_(calculate_inertia()) {
        validate();
    }

    double mass_kg() const { return mass_kg_; }
    double radius_mm() const { return radius_mm_; }
    double inertia_kg_m2() const { return inertia_kg_m2_; }

    /**
     * @brief Кинетическая энергия вращения (Дж)
     */
    double kinetic_energy_j(double angular_velocity_rad_s) const {
        return 0.5 * inertia_kg_m2_ * std::pow(angular_velocity_rad_s, 2);
    }

    /**
     * @brief Момент импульса (кг·м²/с)
     */
    double angular_momentum(double angular_velocity_rad_s) const {
        return inertia_kg_m2_ * angular_velocity_rad_s;
    }

    /**
     * @brief Угловое ускорение от приложенного момента (рад/с²)
     * α = M / J
     */
    double angular_acceleration(double torque_nm) const {
        if (inertia_kg_m2_ <= 0) {
            return 0.0;
        }
        return torque_nm / inertia_kg_m2_;
    }

private:
    double mass_kg_ = 0.0;
    double radius_mm_ = 0.0;
    double inertia_kg_m2_ = 0.0;

    double calculate_inertia() const {
        // Для сплошного диска: J = 0.5 * m * r²
        double radius_m = radius_mm_ * 0.001;
        return 0.5 * mass_kg_ * std::pow(radius_m, 2);
    }

    void validate() const {
        if (mass_kg_ <= 0) {
            throw std::invalid_argument("Flywheel: mass must be positive");
        }
        if (radius_mm_ <= 0) {
            throw std::invalid_argument("Flywheel: radius must be positive");
        }
    }
};

} // namespace cranktrain
