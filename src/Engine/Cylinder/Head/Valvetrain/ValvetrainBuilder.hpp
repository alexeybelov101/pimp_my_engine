#pragma once
#include <memory>
#include <nlohmann/json_fwd.hpp>

class Camshaft;
class CamshaftBuilder;
class Valve;
class Valvetrain;


class ValvetrainBuilder {
    std::unique_ptr<CamshaftBuilder> camBuilder;
public:
    ValvetrainBuilder();
    ~ValvetrainBuilder();

    Valvetrain build(const nlohmann::json& config);
    std::vector<std::vector<Valve>> createLobeValves(const nlohmann::json& config, size_t lobeCount);
};
