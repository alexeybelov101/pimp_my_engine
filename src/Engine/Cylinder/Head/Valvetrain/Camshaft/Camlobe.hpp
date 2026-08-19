#pragma once

class Camlobe {
public:
    Camlobe(double maxLift, double duration);

    double getLift(double angle) const;

private:
    double maxLift;
    double duration;
};
