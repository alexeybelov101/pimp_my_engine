// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once
#include "Structs/Flux.hpp"
#include "Interfaces/IBoundary.hpp"

#include <vector>
#include <functional>

namespace Solvers {

    // Заглушка: полноценный 3-сторонний Riemann solver ещё предстоит написать.
    // Сейчас: разбиваем N границ на пары и считаем HLLC для каждой пары,
    //          а потоки для одной границы усредняем.
    inline std::vector<Flux> RiemannSolver3x(
        const std::vector<std::reference_wrapper<const IBoundary>>& boundaries)
    {
        const size_t n = boundaries.size();
        std::vector<Flux> fluxes(n, Flux());

        // if (n < 2) return fluxes;
        //
        // // Каждая граница i обменивается с соседом i+1 (циклически).
        // // Для n=3 это даст три пары: (0,1), (1,2), (2,0).
        // for (size_t i = 0; i < n; ++i) {
        //     size_t j = (i + 1) % n;
        //
        //     Flux f = HLLC(
        //         boundaries[i].get().getState(),
        //         boundaries[j].get().getState(),
        //         std::min(boundaries[i].get().getArea(),
        //                  boundaries[j].get().getArea())
        //     );
        //
        //     // Каждая граница получает половину потока от каждой из двух пар,
        //     // в которых она участвует.
        //     fluxes[i].mass     += 0.5 * f.mass;
        //     fluxes[i].momentum += 0.5 * f.momentum;
        //     fluxes[i].energy   += 0.5 * f.energy;
        // }

        return fluxes;
    }
}
