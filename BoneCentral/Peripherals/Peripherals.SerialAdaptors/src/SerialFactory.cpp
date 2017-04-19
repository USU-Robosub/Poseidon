//
// Created by Nathan Copier on 1/28/2016.
//

#include "SerialFactory.h"

SerialFactory::SerialFactory() : serial_("/dev/ttyACM0") {}

std::shared_ptr<IThruster> SerialFactory::createLeftForwardThruster() {
    return std::make_shared<SerialThruster>(serial_, MOVE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createRightForwardThruster() {
    return std::make_shared<SerialThruster>(serial_, STRAFE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createLeftStrafeThruster() {
    return std::make_shared<SerialThruster>(serial_, DIVE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createRightStrafeThruster() {
    return std::make_shared<SerialThruster>(serial_, YAW_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createForwardDiveThruster() {
    return std::make_shared<SerialThruster>(serial_, PITCH_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createRearDiveThruster() {
    return std::make_shared<SerialThruster>(serial_, ROLL_IDX);
}

std::shared_ptr<IEscPower> SerialFactory::createEscPower() {
    return std::make_shared<EscPower>(serial_);
}

std::shared_ptr<IHeadlights> SerialFactory::createHeadlights() {
    return std::make_shared<Headlights>(serial_);
}

std::shared_ptr<ITemperatureSensor> SerialFactory::createExternalTemperatureSensor() {
    return std::make_shared<ExTemperatureSensor>();
}

std::shared_ptr<IPressureSensor> SerialFactory::createExternalPressureSensor() {
    return std::make_shared<ExPressureSensor>();
}
