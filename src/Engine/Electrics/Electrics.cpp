// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Electrics.hpp"
#include <utility>

Electrics::Electrics(
    Starter&& starter
):
    starter_(std::move(starter)) {}

void Electrics::step(double dt) {
    starter_.step(dt);
}
