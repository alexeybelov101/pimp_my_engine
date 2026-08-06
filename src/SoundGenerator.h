#pragma once
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>

class SoundGenerator {
public:
    struct Parameters {
        int sample_rate = 44100;
        int bit_depth = 16;
        double duration_seconds = 2.0;
        double amplitude = 0.7;
    };

    struct EngineSoundParams {
        double rpm = 1000.0;
        double throttle = 0.5;
        double load = 0.5;
        int cylinders = 4;
        double overlap = 12.0;
        double compression_ratio = 8.8;
    };

    // Конструктор с параметрами по умолчанию
    SoundGenerator() : params(Parameters()) {}
    explicit SoundGenerator(const Parameters& p) : params(p) {}

    // Генерация звука
    std::vector<double> generate_sweep_tone(
        double rpm_start,
        double rpm_end,
        double duration_seconds,
        const EngineSoundParams& engine_params
    );

    std::vector<double> generate_engine_sound(
        const EngineSoundParams& params,
        double duration_seconds
    );

    // Сохранение в WAV
    bool save_to_wav(const std::vector<double>& samples,
                     const std::string& filename);

    // Воспроизведение (заглушка для Linux)
    void play_sound(const std::vector<double>& samples);

private:
    Parameters params;

    // Акустические модели
    double calculate_firing_frequency(double rpm, int cylinders) const;
    double calculate_exhaust_temperature(double rpm, double load) const;

    // Гармоники
    std::vector<double> generate_harmonics(
        double base_freq,
        double rpm,
        double throttle,
        double load,
        double duration_seconds
    );

    // Огибающая
    std::vector<double> generate_envelope(
        double duration_seconds,
        double rpm,
        double throttle
    );

    // Эффекты
    double apply_doppler_effect(double freq, double velocity) const;
    double apply_resonance(double freq, double rpm, double load) const;
    double apply_exhaust_pulse(double sample, double rpm) const;

    // Вспомогательные
    double normalize(double value) const;
};
