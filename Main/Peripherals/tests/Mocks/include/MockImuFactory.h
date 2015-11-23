//
// Created by Nathan Copier on 11/22/2015.
//

#ifndef PERIPHERALS_MOCK_IMU_FACTORY_H
#define PERIPHERALS_MOCK_IMU_FACTORY_H

#include <IImuFactory.h>
#include "MockAccelerometer.h"
#include "MockCompass.h"
#include "MockPressureSensor.h"

class MockImuFactory : public IImuFactory {
public:
    std::shared_ptr<IPressureSensor> createPressureSensor();
    std::shared_ptr<ICompass> createCompass();
    std::shared_ptr<IAccelerometer> createAccelerometer();
};


#endif //PERIPHERALS_MOCK_IMU_FACTORY_H
