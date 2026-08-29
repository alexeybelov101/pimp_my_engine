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

    for (size_t i = 0; i < lobeCount; ++i) {
        lobePos.emplace_back(
            Camlobe (
                lobeProto["maxLift"].get<double>(),
                lobeProto["duration"].get<double>() * DEG_TO_RAD
            ),
            lobeProto["position"].get<double>() * DEG_TO_RAD
        );
    }

    return Camshaft(std::move(lobePos));
}
