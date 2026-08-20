#pragma once
#include <memory>
#include <nlohmann/json_fwd.hpp>

class ValvetrainBuilder;
class Head;

class HeadBuilder {
public:
    HeadBuilder();
    ~HeadBuilder();

    Head build(const nlohmann::json& config);
private:
    std::unique_ptr<ValvetrainBuilder> valvetrainBuilder;
};
