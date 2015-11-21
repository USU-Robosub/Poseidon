//
// Created by Nathan Copier on 11/21/2015.
//

#ifndef PERIPHERALS_IMU_FACTORY_H
#define PERIPHERALS_IMU_FACTORY_H

#include <IImuFactory.h>
#include <IMU/BMP085.h>
#include <IMU/HMC5883L.h>
#include <IMU/MPU6050.h>


class ImuFactory : public IImuFactory {

public:
    virtual std::shared_ptr<IPressureSensor> createPressureSensor();
    virtual std::shared_ptr<ICompass> createCompass();
    virtual std::shared_ptr<IAccelerometer> createAccelerometer();

};


#endif //PERIPHERALS_IMU_FACTORY_H
