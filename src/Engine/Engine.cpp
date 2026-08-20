#include "Engine.hpp"

Engine::Engine(std::vector<CylPos>&& cylPos):
    cylPos(std::move(cylPos)) {}
