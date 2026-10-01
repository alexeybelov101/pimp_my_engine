// SPDX-License-Identifier: AGPL-3.0-or-later
#include "KinematicsBuilder.hpp"
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/Bank.hpp"
#include "Drive/Drive.hpp"
#include "Kinematics.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

std::unique_ptr<Kinematics> KinematicsBuilder::build(const json& config) {
    return std::make_unique<Kinematics>(
        createFlywheel(config["flywheels"][0]),

    );
}

std::unique_ptr<Flywheel> createFlywheel(const nlohmann::json& config) {
    return std::make_unique<Flywheel>(
        config["mass"].get<double>(),
        config["diameter"].get<double>() * 0.5
    );
}

std::unique_ptr<Crankshaft> createCrankshaft(const nlohmann::json& config) {

}

std::vector<std::unique_ptr<Bank>> createBanks(const nlohmann::json& config) {

}

std::unique_ptr<Drive> createDrive(const nlohmann::json& config) {

}
