#pragma once
#include <memory>
#include <nlohmann/json_fwd.hpp>

class Valve;
class CamshaftBuilder;
class Valvetrain;


class ValvetrainBuilder {
public:
    ValvetrainBuilder();
    ~ValvetrainBuilder();

    Valvetrain build(const nlohmann::json& config);
private:
    std::unique_ptr<CamshaftBuilder> camshaftBuilder;

    std::vector<std::vector<Valve>> createLobeValves(const nlohmann::json& config, size_t lobeCount);
};
