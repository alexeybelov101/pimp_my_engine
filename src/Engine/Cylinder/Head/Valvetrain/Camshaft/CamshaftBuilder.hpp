#pragma once
#include <nlohmann/json_fwd.hpp>

class Camlobe;
class Camshaft;

class CamshaftBuilder {
public:
    static Camshaft build(const nlohmann::json& config);
};
