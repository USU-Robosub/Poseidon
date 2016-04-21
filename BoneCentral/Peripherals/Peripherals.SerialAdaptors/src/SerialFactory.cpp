//
// Created by Nathan Copier on 1/28/2016.
//

#include "../include/SerialFactory.h"

std::shared_ptr<IThruster> SerialFactory::createLeftForwardThruster() {
    return std::make_shared<SerialThruster>(serial_, LEFT_FORWARD);
}
std::shared_ptr<IThruster> SerialFactory::createRightForwardThruster() {
    return std::make_shared<SerialThruster>(serial_, RIGHT_FORWARD);
}
std::shared_ptr<IThruster> SerialFactory::createLeftStrafeThruster() {
    return std::make_shared<SerialThruster>(serial_, LEFT_STRAFE);
}
std::shared_ptr<IThruster> SerialFactory::createRightStrafeThruster() {
    return std::make_shared<SerialThruster>(serial_, RIGHT_STRAFE);
}
std::shared_ptr<IThruster> SerialFactory::createForwardDiveThruster() {
    return std::make_shared<SerialThruster>(serial_, FRONT_DIVE);
}
std::shared_ptr<IThruster> SerialFactory::createRearDiveThruster() {
    return std::make_shared<SerialThruster>(serial_, BACK_DIVE);
}
std::shared_ptr<IEscPower> SerialFactory::createEscPower() {
    return std::make_shared<EscPower>(serial_);
}
std::shared_ptr<IHeadlights> SerialFactory::createHeadlights() {
    return std::make_shared<Headlights>(serial_);
}
