#include "Head.hpp"
#include "Valvetrain/Valvetrain.hpp"
#include <utility>

Head::Head(
    double chamberVolume,
    Valvetrain&& intakeValvetrain,
    Valvetrain&& exhaustValvetrain,
    Pipe* intakePipe,
    Pipe* exhaustPipe
) : chamberVolume(chamberVolume),
    intakeValvetrain(std::move(intakeValvetrain)),
    exhaustValvetrain(std::move(exhaustValvetrain)),
    intakePipe(intakePipe),
    exhaustPipe(exhaustPipe) {}

double Head::getChamberVolume() const {
    return chamberVolume;
}

double Head::getIntakeLift(double angle) const {
    return intakeValvetrain.getLift(angle);
}

double Head::getExhaustLift(double angle) const {
    return exhaustValvetrain.getLift(angle);
}

double Head::getIntakeFlowArea(double angle) const {
    return intakeValvetrain.getTotalFlowArea(angle);
}

double Head::getExhaustFlowArea(double angle) const {
    return exhaustValvetrain.getTotalFlowArea(angle);
}

void Head::setIntakePipe(Pipe* pipe) {
    intakePipe = pipe;
}

void Head::setExhaustPipe(Pipe* pipe) {
    exhaustPipe = pipe;
}
