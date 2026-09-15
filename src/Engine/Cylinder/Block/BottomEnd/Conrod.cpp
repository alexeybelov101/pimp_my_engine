// SPDX-License-Identifier: AGPL-3.0-or-later
#include "Conrod.hpp"

Conrod::Conrod(double length): length_(length) {}

double Conrod::getLength() const {
    return length_;
}
