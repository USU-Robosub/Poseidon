//
// Created by Nathan Copier on 1/28/2016.
//

#include "SerialFactory.h"

#define Pin_9_15 48

SerialFactory::SerialFactory(std::ostream& out) : out_(out), serial_("/dev/ttyUSB0") { }

std::shared_ptr<IThruster> SerialFactory::createMoveThruster() {
    return std::make_shared<SerialThruster>(serial_, MOVE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createStrafeThruster() {
    return std::make_shared<SerialThruster>(serial_, STRAFE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createDiveThruster() {
    return std::make_shared<SerialThruster>(serial_, DIVE_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createYawThruster() {
    return std::make_shared<SerialThruster>(serial_, YAW_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createPitchThruster() {
    return std::make_shared<SerialThruster>(serial_, PITCH_IDX);
}

std::shared_ptr<IThruster> SerialFactory::createRollThruster() {
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

std::shared_ptr<ActionThread> SerialFactory::createArduinoAction() {
    return std::make_shared<ActionThread>(Pin_9_15, out_);
}

#undef Pin_9_15