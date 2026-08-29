#pragma once
#include <nlohmann/json_fwd.hpp>

class ValvetrainBuilder;
class Head;

class HeadBuilder {
public:
    static Head build(const nlohmann::json& config);
};
