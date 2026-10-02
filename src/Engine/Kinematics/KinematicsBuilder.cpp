// SPDX-License-Identifier: AGPL-3.0-or-later
#include "KinematicsBuilder.hpp"
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/CrankshaftBuilder.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/Bank.hpp"
#include "Bank/Head/Valvetrain/Valvetrain.hpp"
#include "Drive/Drive.hpp"
#include "Kinematics.hpp"
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

using json = nlohmann::json;

std::unique_ptr<Kinematics> KinematicsBuilder::build(const json& config) {
    std::unique_ptr<Flywheel> flywheel = createFlywheel(config["flywheel"]);
    std::unique_ptr<Crankshaft> crankshaft = CrankshaftBuilder::build(config["crankshaft"], *flywheel);
    std::vector<std::unique_ptr<Bank>> banks = BankBuilder::build(config["banks"], *crankshaft);
    std::unique_ptr<Drive> drive = createDrive(*crankshaft, valvetrains);
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

std::unique_ptr<Drive> createDrive(Crankshaft& crankshaft, std::vector<Valvetrain*> valvetrains) {
    return std::make_unique<Drive>(
        crankshaft,
        valvetrains
    );
}
