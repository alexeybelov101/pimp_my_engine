#pragma once
#include <vector>
#include "Camlobe.hpp"

class Camshaft {
public:
    Camshaft(const std::vector<Camlobe>& lobes);

    double get_lift(int lobe_index, double angle) const;

private:
    std::vector<Camlobe> lobes;
};
