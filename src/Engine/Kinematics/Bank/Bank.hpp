// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Head/Head.hpp"
#include "Block/Block.hpp"

class Bank {
public:
    Bank(
        double position,
        Head&& head,
        Block&& block
    );

    void step(double dt);

private:
    const double position_;
    Head head_;
    Block block_;
};

