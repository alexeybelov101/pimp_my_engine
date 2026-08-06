#pragma once
#include "Engine.h"
#include "ConfigReader.h"
#include <memory>

class EngineFactory {
public:
    static Engine create_from_config(const ConfigReader& config);
};
