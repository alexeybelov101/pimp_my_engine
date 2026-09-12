#include "Utility/ConfigReader.hpp"
#include "Utility/ArgsParser.hpp"
#include "Engine/EngineBuilder.hpp"
#include "Engine/Engine.hpp"
#include <nlohmann/json.hpp>
#include <numbers>
#include <chrono>
#include <iostream>
#include <numbers>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    auto settings = ArgsParser::parse(argc, argv);


    const double dt = 1.0 / settings.frequency;

    const double simulationTime = settings.time;
    const int steps = static_cast<int>(simulationTime / dt);


    Engine engine = EngineBuilder::build(
        ConfigReader::read(settings.configPath),
        dt
    );

    engine.setOmega(settings.rpm / 30.0 * std::numbers::pi);



    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < steps; ++i) {
        engine.step(dt);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "elapsed time: " << end - start << std::endl;

    return 0;
}
