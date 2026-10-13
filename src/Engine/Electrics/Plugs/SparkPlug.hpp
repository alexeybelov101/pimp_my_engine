#pragma once

class Cylinder;

class SparkPlug {
public:
    SparkPlug(double gap, double resistor);

    void fire();

private:
    double gap_;
    double resistor_;
    Cylinder* cylinder_;
};
