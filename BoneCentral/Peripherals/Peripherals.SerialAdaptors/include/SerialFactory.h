//
// Created by Nathan Copier on 1/28/2016.
//

#ifndef PERIPHERALS_SERIAL_FACTORY_H
#define PERIPHERALS_SERIAL_FACTORY_H

#include <IThrusterFactory.h>
#include <ostream>
#include "ActionThread.h"
#include "SerialThruster.h"
#include "EscPower.h"
#include "Headlights.h"
#include "ExTemperatureSensor.h"
#include "ExPressureSensor.h"
#include "Serial.h"


class SerialFactory : public IThrusterFactory {
private:
    std::ostream& out_;
    Serial serial_, event_;
    
public:
    SerialFactory(std::ostream& out);
    std::shared_ptr<IThruster> createMoveThruster();
    std::shared_ptr<IThruster> createStrafeThruster();
    std::shared_ptr<IThruster> createDiveThruster();
    std::shared_ptr<IThruster> createYawThruster();
    std::shared_ptr<IThruster> createPitchThruster();
    std::shared_ptr<IThruster> createRollThruster();
    std::shared_ptr<ITemperatureSensor> createExternalTemperatureSensor();
    std::shared_ptr<IPressureSensor> createExternalPressureSensor();
    std::shared_ptr<IEscPower> createEscPower();
    std::shared_ptr<IHeadlights> createHeadlights();
    std::shared_ptr<ActionThread> createArduinoAction();
};


#endif //PERIPHERALS_SERIAL_FACTORY_H
