#pragma once
#include <nlohmann/json_fwd.hpp>

class Pipe;

class PipeBuilder {
public:
    static Pipe build(const nlohmann::json& config, double dt);
};
