#pragma once

class Valve {
public:
    Valve(double headDiameter, double sinSeatA, double cosSeatA);

    double getFlowArea(double lift) const;

private:
    double headDiameter;
    double sinSeatA;
    double cosSeatA;
};
