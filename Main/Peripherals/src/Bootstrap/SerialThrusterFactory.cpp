//
// Created by Nathan Copier on 1/28/2016.
//

#include "SerialThrusterFactory.h"

SerialThrusterFactory::SerialThrusterFactory(Serial serial) : serial_(serial) {}
std::shared_ptr<IThruster> SerialThrusterFactory::createLeftForwardThruster() {
    return std::make_shared<SerialThruster>(&serial_, LEFT_FORWARD);
}
std::shared_ptr<IThruster> SerialThrusterFactory::createRightForwardThruster() {
    return std::make_shared<SerialThruster>(&serial_, RIGHT_FORWARD);
}
std::shared_ptr<IThruster> SerialThrusterFactory::createLeftStrafeThruster() {
    return std::make_shared<SerialThruster>(&serial_, LEFT_STRAFE);
}
std::shared_ptr<IThruster> SerialThrusterFactory::createRightStrafeThruster() {
    return std::make_shared<SerialThruster>(&serial_, RIGHT_STRAFE);
}
std::shared_ptr<IThruster> SerialThrusterFactory::createForwardDiveThruster() {
    return std::make_shared<SerialThruster>(&serial_, FRONT_DIVE);
}
std::shared_ptr<IThruster> SerialThrusterFactory::createRearDiveThruster() {
    return std::make_shared<SerialThruster>(&serial_, BACK_DIVE);
}
