// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Battery {
public:
    Battery(double resistance);

    void step(double dt);
private:
    double resistance_;
};
