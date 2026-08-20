#include "CamshaftBuilder.hpp"
#include "Camlobe.hpp"
#include "Camshaft.hpp"
#include <nlohmann/json.hpp>
#include <utility>

#define _USE_MATH_DEFINES
#include <cmath>
#define DEG_TO_RAD (M_PI / 180.0)

using json = nlohmann::json;

Camshaft CamshaftBuilder::build(const json& config) {
    std::vector<Camshaft::LobePos> lobePos;

    const auto& lobeProto = config["lobe"]["prototype"];

    const int lobeCount = config["lobe"]["count"];
    lobePos.reserve(lobeCount);

    Camlobe templateLobe(
        lobeProto["maxLift"].get<double>(),
        lobeProto["duration"].get<double>() * DEG_TO_RAD
    );
    double position = lobeProto["position"].get<double>() * DEG_TO_RAD;

    for (int i = 0; i < lobeCount; ++i) {
        lobePos.push_back({templateLobe, position});
    }

    return Camshaft(std::move(lobePos));
}
