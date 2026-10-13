// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Starter/Starter.hpp"

class Electrics {
public:
    Electrics(
        Starter&& starter
    );

    void step(double dt);
private:
    Starter starter_;
};
