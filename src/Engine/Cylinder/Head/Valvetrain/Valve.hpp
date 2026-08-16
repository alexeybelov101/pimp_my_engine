#pragma once

class Valve {
public:
    Valve(double headDiameter, double seatAngle);

    double getFlowArea(double lift) const;

private:
    double headDiameter;
    double seatAngle;
};
