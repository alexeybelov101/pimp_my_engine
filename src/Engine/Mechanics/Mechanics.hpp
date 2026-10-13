// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include <vector>
#include <memory>
#include "Flywheel/Flywheel.hpp"
#include "Crankshaft/Crankshaft.hpp"
#include "Bank/Block/Block.hpp"
#include "Bank/Bank.hpp"
#include "Drive/Drive.hpp"
#include <memory>

class Mechanics {
public:
    Mechanics(
        std::unique_ptr<Flywheel>&& flywheel,
        std::unique_ptr<Crankshaft>&& crankshaft,
        std::vector<std::unique_ptr<Bank>>&& banks,
        Drive&& drive
    );

    void setOmega(double omega);
    void step(double dt);

private:
    std::unique_ptr<Flywheel> flywheel_;
    std::unique_ptr<Crankshaft> crankshaft_;
    std::vector<std::unique_ptr<Bank>> banks_;
    Drive drive_;
};
