// SPDX-License-Identifier: AGPL-3.0-or-later
#include "KinematicsBuilder.hpp"
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/CrankshaftBuilder.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/BankBuilder.hpp"
#include "Bank/Bank.hpp"
#include "Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Drive/Drive.hpp"
#include "Kinematics.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

constexpr double G_TO_KG = 1.0e-3;
constexpr double MM_TO_M = 1.0e-3;

std::unique_ptr<Kinematics> KinematicsBuilder::build(const json& config) {
    auto flywheel = createFlywheel(config["flywheel"]);
    auto crankshaft = CrankshaftBuilder::build(config["crankshaft"], *flywheel);
    std::vector<std::unique_ptr<Bank>> banks = BankBuilder::build(config["banks"], crankshaft.get());
    Drive drive = createDrive(crankshaft.get(), &banks);
    return std::make_unique<Kinematics>(
        std::move(flywheel),
        std::move(crankshaft),
        std::move(banks),
        std::move(drive)
    );
}

std::unique_ptr<Flywheel> KinematicsBuilder::createFlywheel(const json& config) {
    return std::make_unique<Flywheel>(
        config["mass"].get<double>() * G_TO_KG,
        config["diameter"].get<double>() * 0.5 * MM_TO_M
    );
}

Drive KinematicsBuilder::createDrive(Crankshaft* crankshaft, std::vector<std::unique_ptr<Bank>>* banks) {
    std::vector<Valvetrain*> valvetrains;
    for (auto& bank : *banks) {
        const auto& bv = bank->getValvetrains();
        valvetrains.insert(valvetrains.end(), bv.begin(), bv.end());
    }

    return Drive(
        crankshaft,
        std::move(valvetrains)
    );
}
