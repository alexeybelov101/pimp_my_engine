#pragma once
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <unordered_map>

namespace valvetrain {

/**
 * @brief Математическое описание профиля подъема клапана
 * 
 * Поддерживает различные типы профилей:
 * - SINUSOIDAL: плавный синусоидальный профиль
 * - CYCLOIDAL: циклоидальный профиль для высоких оборотов
 * - POLYNOMIAL: полиномиальный профиль (3-й степени)
 * - CUSTOM: пользовательская функция
 */
class CamProfile {
public:
    enum class Type {
        SINUSOIDAL,
        CYCLOIDAL,
        POLYNOMIAL,
        CUSTOM
    };

    using CustomFunction = std::function<double(double)>;

    CamProfile() = default;

    explicit CamProfile(Type type, double max_lift_mm)
        : type_(type), max_lift_mm_(max_lift_mm) {
        validate();
    }

    CamProfile(CustomFunction func, double max_lift_mm)
        : type_(Type::CUSTOM), max_lift_mm_(max_lift_mm), custom_func_(std::move(func)) {
        validate();
    }

    Type type() const { return type_; }
    double max_lift_mm() const { return max_lift_mm_; }

    /**
     * @brief Расчет подъема клапана в зависимости от угла поворота распредвала
     * @param angle_deg Угол поворота (0..duration)
     * @param duration_deg Полная длительность открытия (градусы)
     * @return Подъем клапана в мм
     */
    double lift_at_angle(double angle_deg, double duration_deg) const {
        if (duration_deg <= 0 || angle_deg < 0 || angle_deg > duration_deg) {
            return 0.0;
        }

        double ratio = angle_deg / duration_deg; // 0..1
        double base_lift = calculate_base_lift(ratio);

        return base_lift * max_lift_mm_;
    }

    /**
     * @brief Расчет скорости подъема клапана (мм/град)
     */
    double velocity_at_angle(double angle_deg, double duration_deg) const {
        if (duration_deg <= 0 || angle_deg < 0 || angle_deg > duration_deg) {
            return 0.0;
        }

        double ratio = angle_deg / duration_deg;
        double delta = 0.001;
        double lift1 = calculate_base_lift(ratio);
        double lift2 = calculate_base_lift(std::min(ratio + delta, 1.0));

        return (lift2 - lift1) / delta * max_lift_mm_;
    }

    /**
     * @brief Расчет ускорения клапана (мм/град²)
     */
    double acceleration_at_angle(double angle_deg, double duration_deg) const {
        if (duration_deg <= 0 || angle_deg < 0 || angle_deg > duration_deg) {
            return 0.0;
        }

        double v1 = velocity_at_angle(angle_deg, duration_deg);
        double v2 = velocity_at_angle(angle_deg + 0.001, duration_deg);

        return (v2 - v1) / 0.001;
    }

private:
    Type type_ = Type::SINUSOIDAL;
    double max_lift_mm_ = 0.0;
    CustomFunction custom_func_;

    void validate() const {
        if (max_lift_mm_ <= 0) {
            throw std::invalid_argument("CamProfile: max_lift must be positive");
        }
    }

    double calculate_base_lift(double ratio) const {
        switch (type_) {
            case Type::SINUSOIDAL:
                return 0.5 * (1.0 - std::cos(M_PI * ratio));

            case Type::CYCLOIDAL:
                return ratio - std::sin(2.0 * M_PI * ratio) / (2.0 * M_PI);

            case Type::POLYNOMIAL:
                return 10.0 * std::pow(ratio, 3) - 15.0 * std::pow(ratio, 4) + 
                       6.0 * std::pow(ratio, 5);

            case Type::CUSTOM:
                if (custom_func_) {
                    return custom_func_(ratio);
                }
                return 0.0;

            default:
                return 0.5 * (1.0 - std::cos(M_PI * ratio));
        }
    }
};


/**
 * @brief Экземпляр кулачка с профилем и фазой
 */
class CamLobe {
public:
    CamLobe() = default;

    CamLobe(const CamProfile& profile, 
            double opening_angle_deg,
            double closing_angle_deg)
        : profile_(profile)
        , opening_angle_deg_(opening_angle_deg)
        , closing_angle_deg_(closing_angle_deg) {
        validate();
    }

    const CamProfile& profile() const { return profile_; }
    double opening_angle_deg() const { return opening_angle_deg_; }
    double closing_angle_deg() const { return closing_angle_deg_; }

    /**
     * @brief Длительность открытия в градусах
     */
    double duration_deg() const {
        return closing_angle_deg_ - opening_angle_deg_;
    }

    /**
     * @brief Текущий подъем клапана при заданном угле распредвала
     */
    double current_lift(double cam_angle_deg) const {
        if (cam_angle_deg < opening_angle_deg_ || cam_angle_deg > closing_angle_deg_) {
            return 0.0;
        }

        double relative_angle = cam_angle_deg - opening_angle_deg_;
        return profile_.lift_at_angle(relative_angle, duration_deg());
    }

    /**
     * @brief Проверка, открыт ли клапан
     */
    bool is_open(double cam_angle_deg) const {
        return cam_angle_deg >= opening_angle_deg_ && 
               cam_angle_deg <= closing_angle_deg_;
    }

private:
    CamProfile profile_;
    double opening_angle_deg_ = 0.0;
    double closing_angle_deg_ = 0.0;

    void validate() const {
        if (closing_angle_deg_ <= opening_angle_deg_) {
            throw std::invalid_argument("CamLobe: closing angle must be > opening angle");
        }
    }
};


/**
 * @brief Распредвал (впускной или выпускной)
 */
class CamShaft {
public:
    enum class Type {
        INTAKE,
        EXHAUST
    };

    CamShaft() = default;

    explicit CamShaft(Type type)
        : type_(type) {}

    Type type() const { return type_; }

    /**
     * @brief Добавление кулачка для цилиндра
     * @param cylinder_index Индекс цилиндра (0..N-1)
     * @param lobe Кулачок
     */
    void add_lobe(int cylinder_index, const CamLobe& lobe) {
        if (cylinder_index < 0) {
            throw std::invalid_argument("CamShaft: cylinder index must be non-negative");
        }
        lobes_[cylinder_index] = lobe;
    }

    /**
     * @brief Получение кулачка для цилиндра
     */
    const CamLobe* get_lobe(int cylinder_index) const {
        auto it = lobes_.find(cylinder_index);
        if (it != lobes_.end()) {
            return &it->second;
        }
        return nullptr;
    }

    /**
     * @brief Общий подъем всех клапанов при заданном угле
     */
    double total_lift(int cylinder_index, double cam_angle_deg) const {
        const CamLobe* lobe = get_lobe(cylinder_index);
        if (!lobe) {
            return 0.0;
        }
        return lobe->current_lift(cam_angle_deg);
    }

    /**
     * @brief Количество кулачков
     */
    size_t lobe_count() const { return lobes_.size(); }

    /**
     * @brief Установка угла поворота распредвала
     */
    void set_angle_deg(double angle) {
        current_angle_deg_ = std::fmod(angle, 720.0);
        if (current_angle_deg_ < 0) {
            current_angle_deg_ += 720.0;
        }
    }

    double current_angle_deg() const { return current_angle_deg_; }

private:
    Type type_ = Type::INTAKE;
    std::unordered_map<int, CamLobe> lobes_;
    double current_angle_deg_ = 0.0;
};


/**
 * @brief Клапан ГРМ
 */
class Valve {
public:
    enum class Position {
        CLOSED,
        OPENING,
        OPEN,
        CLOSING
    };

    Valve() = default;

    Valve(double mass_kg, double diameter_mm, double spring_preload_n = 0.0)
        : mass_kg_(mass_kg)
        , diameter_mm_(diameter_mm)
        , spring_preload_n_(spring_preload_n) {
        validate();
    }

    double mass_kg() const { return mass_kg_; }
    double diameter_mm() const { return diameter_mm_; }
    double spring_preload_n() const { return spring_preload_n_; }

    /**
     * @brief Площадь проходного сечения клапана
     */
    double flow_area_mm2() const {
        return M_PI * std::pow(diameter_mm_ / 2.0, 2);
    }

    /**
     * @brief Масса в граммах
     */
    double mass_g() const { return mass_kg_ * 1000.0; }

    /**
     * @brief Инерция клапана (упрощенно)
     */
    double inertia() const {
        return mass_kg_ * std::pow(diameter_mm_ * 0.001 / 2.0, 2) / 2.0;
    }

private:
    double mass_kg_ = 0.0;
    double diameter_mm_ = 0.0;
    double spring_preload_n_ = 0.0;

    void validate() const {
        if (mass_kg_ <= 0) {
            throw std::invalid_argument("Valve: mass must be positive");
        }
        if (diameter_mm_ <= 0) {
            throw std::invalid_argument("Valve: diameter must be positive");
        }
    }
};


/**
 * @brief Головка цилиндра - объединяет два распредвала и клапаны
 */
class Head {
public:
    Head() = default;

    Head(const CamShaft& intake_cam,
         const CamShaft& exhaust_cam,
         const Valve& intake_valve,
         const Valve& exhaust_valve)
        : intake_cam_(intake_cam)
        , exhaust_cam_(exhaust_cam)
        , intake_valve_(intake_valve)
        , exhaust_valve_(exhaust_valve) {}

    const CamShaft& intake_cam() const { return intake_cam_; }
    const CamShaft& exhaust_cam() const { return exhaust_cam_; }
    const Valve& intake_valve() const { return intake_valve_; }
    const Valve& exhaust_valve() const { return exhaust_valve_; }

    /**
     * @brief Текущий подъем впускного клапана
     */
    double intake_lift(int cylinder_index) const {
        return intake_cam_.total_lift(cylinder_index, intake_cam_.current_angle_deg());
    }

    /**
     * @brief Текущий подъем выпускного клапана
     */
    double exhaust_lift(int cylinder_index) const {
        return exhaust_cam_.total_lift(cylinder_index, exhaust_cam_.current_angle_deg());
    }

    /**
     * @brief Проверка, открыт ли впускной клапан
     */
    bool is_intake_open(int cylinder_index) const {
        const CamLobe* lobe = intake_cam_.get_lobe(cylinder_index);
        return lobe && lobe->is_open(intake_cam_.current_angle_deg());
    }

    /**
     * @brief Проверка, открыт ли выпускной клапан
     */
    bool is_exhaust_open(int cylinder_index) const {
        const CamLobe* lobe = exhaust_cam_.get_lobe(cylinder_index);
        return lobe && lobe->is_open(exhaust_cam_.current_angle_deg());
    }

    /**
     * @brief Перекрытие клапанов (оба открыты)
     */
    bool is_overlap(int cylinder_index) const {
        return is_intake_open(cylinder_index) && is_exhaust_open(cylinder_index);
    }

    /**
     * @brief Эффективная площадь впуска с учетом подъема клапана
     */
    double effective_intake_area(int cylinder_index) const {
        double lift = intake_lift(cylinder_index);
        if (lift <= 0) {
            return 0.0;
        }

        // Площадь кольцевой щели вокруг клапана
        double valve_dia_m = intake_valve_.diameter_mm() * 0.001;
        double lift_m = lift * 0.001;

        // A = π * D * L (приближенно)
        return M_PI * valve_dia_m * lift_m;
    }

    /**
     * @brief Эффективная площадь выпуска
     */
    double effective_exhaust_area(int cylinder_index) const {
        double lift = exhaust_lift(cylinder_index);
        if (lift <= 0) {
            return 0.0;
        }

        double valve_dia_m = exhaust_valve_.diameter_mm() * 0.001;
        double lift_m = lift * 0.001;

        return M_PI * valve_dia_m * lift_m;
    }

private:
    CamShaft intake_cam_;
    CamShaft exhaust_cam_;
    Valve intake_valve_;
    Valve exhaust_valve_;
};

} // namespace valvetrain
