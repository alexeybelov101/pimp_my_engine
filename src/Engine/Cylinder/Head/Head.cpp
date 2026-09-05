#include "Head.hpp"
#include "Valvetrain/Valvetrain.hpp"
#include <utility>

Head::Head(
    double chamberVolume,
    Valvetrain&& intakeValvetrain,
    Valvetrain&& exhaustValvetrain
) : chamberVolume_(chamberVolume),
    intakeValvetrain_(std::move(intakeValvetrain)),
    exhaustValvetrain_(std::move(exhaustValvetrain)) {}

double Head::getChamberVolume() const {
    return chamberVolume_;
}

double Head::getIntakeLift(double angle) const {
    return intakeValvetrain_.getLift(angle);
}

double Head::getExhaustLift(double angle) const {
    return exhaustValvetrain_.getLift(angle);
}

double Head::getIntakeFlowArea(double angle) const {
    return intakeValvetrain_.getTotalFlowArea(angle);
}

double Head::getExhaustFlowArea(double angle) const {
    return exhaustValvetrain_.getTotalFlowArea(angle);
}
