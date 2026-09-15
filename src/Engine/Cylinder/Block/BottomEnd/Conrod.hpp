// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma once

class Conrod {
public:
    explicit Conrod(double length);

    double getLength() const;

private:
    double length_;
};
