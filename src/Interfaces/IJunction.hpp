// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class IJunction {
public:
    virtual ~IJunction() = default;
    virtual void calculateBoundaryFluxes() const = 0;
};
