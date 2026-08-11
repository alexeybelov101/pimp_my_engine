#pragma once

class Valve {
    public:
        explicit Valve(double head_diameter);

        double get_flow_area(double lift) const;

    private:
        double head_diameter;
};
