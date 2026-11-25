#pragma once

class Cylinder;

class SparkPlug {
public:
    SparkPlug(double gap, double resistor);

    double getUBreak() const;
    void fire();

private:
    double gap_;
    double resistor_;
    Cylinder* cylinder_;

    bool isArcing_;
};
