// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Coil.hpp"

Coil::Coil(
    Winding primary,
    Winding secondary
):
    primary_(primary),
    secondary_(secondary) {}
