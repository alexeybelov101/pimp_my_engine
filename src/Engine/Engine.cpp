#include "Engine.hpp"
#include <iostream>

Engine::Engine(std::vector<CylPos>&& cylPos):
    cylPos(std::move(cylPos)) {}

void Engine::do_a_barrel_roll() {
    for (const auto& x : cylPos) {
        std::cout << x.position << "\n";
    }
}
