// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Starter {
public:
    Starter(double resistance);

    void step(double dt);
private:
    double resistance_;
};
