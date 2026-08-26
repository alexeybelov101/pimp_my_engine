#include "ConfigReader/ConfigReader.hpp"
#include "Engine/EngineBuilder.hpp"
#include "Engine/Engine.hpp"

#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    json config = ConfigReader::read("сonfigs/config.json");

    std::cout << config.dump(4) << std::endl;

    Engine engine = EngineBuilder::build(config["engine"]);

    return 0;
}
