#pragma once
#include <nlohmann/json_fwd.hpp>

class Valve;
class Valvetrain;

class ValvetrainBuilder {
public:
    static Valvetrain build(const nlohmann::json& config);
private:
    static std::vector<std::vector<Valve>> createLobeValves(const nlohmann::json& config, size_t lobeCount);
};
