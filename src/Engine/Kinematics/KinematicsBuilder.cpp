// SPDX-License-Identifier: AGPL-3.0-or-later
#include "KinematicsBuilder.hpp"
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/CrankshaftBuilder.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/Bank.hpp"
#include "Drive/Drive.hpp"
#include "Kinematics.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

std::unique_ptr<Kinematics> KinematicsBuilder::build(const json& config) {
    std::unique_ptr<Flywheel> flywheel = createFlywheel(config["flywheel"]);
    std::unique_ptr<Crankshaft> crankshaft = CrankshaftBuilder::build(config["crankshaft"], *flywheel);

    return std::make_unique<Kinematics>(
        flywheel,
        crankshaft,
        banks,
        drive
    );
}

std::unique_ptr<Flywheel> createFlywheel(const json& config) {
    return std::make_unique<Flywheel>(
        config["mass"].get<double>(),
        config["diameter"].get<double>() * 0.5
    );
}

std::vector<std::unique_ptr<Bank>> createBanks(const json& config) {

}

std::unique_ptr<Drive> createDrive(const json& config) {

}
