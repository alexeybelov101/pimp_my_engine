// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <nlohmann/json_fwd.hpp>
#include <memory>
#include <vector>

class Flywheel;
class Crankshaft;
class Bank;
class Drive;
class Kinematics;

class KinematicsBuilder {
public:
    static std::unique_ptr<Kinematics> build(const nlohmann::json& config);

private:
    static std::unique_ptr<Flywheel> createFlywheel(const nlohmann::json& config);
    static Drive createDrive(Crankshaft* crankshaft, std::vector<std::unique_ptr<Bank>>* banks);
};
