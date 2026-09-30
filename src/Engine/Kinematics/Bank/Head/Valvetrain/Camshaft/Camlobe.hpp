// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Camlobe {
public:
    Camlobe(double maxLift, double duration);

    double getLift(double angle) const;

private:
    double maxLift_;
    double duration_;
};
