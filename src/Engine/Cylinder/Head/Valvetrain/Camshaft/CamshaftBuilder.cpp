#include "CamshaftBuilder.hpp"
#include "Camlobe.hpp"
#include "Camshaft.hpp"
#include <nlohmann/json.hpp>
#include <utility>
#include <numbers>

constexpr double DEG_TO_RAD = std::numbers::pi / 180.0;

using json = nlohmann::json;

Camshaft CamshaftBuilder::build(const json& config) {
    std::vector<Camshaft::LobePos> lobePos;

    const auto& lobeProto = config["lobe"]["prototype"];

    const size_t lobeCount = config["lobe"]["count"].get<size_t>();
    lobePos.reserve(lobeCount);

    Camlobe templateLobe(
        lobeProto["maxLift"].get<double>(),
        lobeProto["duration"].get<double>() * DEG_TO_RAD
    );
    double position = lobeProto["position"].get<double>() * DEG_TO_RAD;

    for (size_t i = 0; i < lobeCount; ++i) {
        lobePos.push_back({templateLobe, position});
    }

    return Camshaft(std::move(lobePos));
}
