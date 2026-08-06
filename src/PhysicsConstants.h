#pragma once
#include <cmath>

namespace PhysicsConstants {
    // Термодинамика
    constexpr double R_SPECIFIC_AIR = 287.0;        // J/(kg*K)
    constexpr double CV_AIR = 718.0;                // J/(kg*K) при постоянном объеме
    constexpr double CP_AIR = 1005.0;               // J/(kg*K) при постоянном давлении
    constexpr double GAMMA_AIR = 1.4;               // Показатель адиабаты (было 1.35)
    constexpr double T_AMBIENT = 293.0;             // K (20°C)
    constexpr double T_INTAKE = 310.0;              // K (подогрев во впуске ~37°C)

    // Топливо (бензин АИ-93)
    constexpr double LHV_GASOLINE = 44.0e6;         // J/kg (низшая теплота сгорания)
    constexpr double DENSITY_GASOLINE = 750.0;      // kg/m³

    // Воздух
    constexpr double RHO_AIR_STP = 1.225;           // kg/m³ при 15°C
    constexpr double RHO_AIR_INTAKE = 1.15;         // kg/m³ (было 1.05, увеличено)
    constexpr double SPEED_OF_SOUND = 343.0;        // m/s при 20°C

    // Давление
    constexpr double ATMOSPHERIC_PRESSURE = 101325.0; // Pa
    constexpr double EXHAUST_PRESSURE = 105000.0;    // Pa (было 110000)
    constexpr double INTAKE_PRESSURE = 98000.0;      // Pa (разрежение во впуске)

    // Двигатель
    constexpr double MAX_PRESSURE = 120e5;           // Pa (было 90e5)
    constexpr double MIN_PRESSURE = 15e5;            // Pa (было 20e5)

    // Преобразования
    constexpr double CC_TO_M3 = 1e-6;
    constexpr double MM_TO_M = 0.001;
    constexpr double CM_TO_M = 0.01;
    constexpr double RPM_TO_RAD_PER_SEC = 2.0 * M_PI / 60.0;
    constexpr double HP_TO_WATT = 745.7;

    // Коэффициенты для расчета VE
    constexpr double VALVE_DISCHARGE_COEFF = 0.7;
    constexpr double MAX_FLOW_VELOCITY = 120.0;     // m/s
}
