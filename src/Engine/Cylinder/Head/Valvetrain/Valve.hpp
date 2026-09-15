// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Valve {
public:
    Valve(
        double headRadius,
        double sinSeatA,
        double cosSeatA
    );

    double getFlowArea(double lift) const;
    double getValveArea() const;

private:
    double headRadius_;
    double sinSeatA_;
    double cosSeatA_;
};
