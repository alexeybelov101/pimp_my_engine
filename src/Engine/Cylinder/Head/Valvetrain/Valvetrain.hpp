#pragma once
#include <vector>
#include "Camshaft.hpp"
#include "Valve.hpp"

class Valvetrain {
    public:
        Valvetrain(
            const std::vector<Camshaft>& camshafts,
            const std::vector<Valve>& valves
        );

        double get_air_flow_for_valve(int lobe_index, double angle) const;
        double get_total_air_flow();

    private:
        std::vector<Camshaft> camshafts;
        std::vector<Valve> valves;
};
