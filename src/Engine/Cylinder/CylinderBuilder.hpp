#pragma once
#include <memory>
#include <nlohmann/json_fwd.hpp>

class HeadBuilder;
class BlockBuilder;
class Cylinder;

class CylinderBuilder {
public:
    CylinderBuilder();
    ~CylinderBuilder();

    Cylinder build(const nlohmann::json& config);
private:
    std::unique_ptr<HeadBuilder> headBuilder;
    std::unique_ptr<BlockBuilder> blockBuilder;
};
