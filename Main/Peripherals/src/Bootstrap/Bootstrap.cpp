//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <cstring>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"
#include "EscPower.h"
#include <Headlights.h>
#include <MPU6050.h>
#include <HMC5883L.h>
#include <BMP085.h>
#include <ImuPower.h>
#include <ImuFactory.h>

int main() {

    auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
    auto serial = Serial();
    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, scriptLogger);


    auto mpu = std::make_shared<MPU6050>();
    auto hmc = std::make_shared<HMC5883L>();
    auto bmp = std::make_shared<BMP085>();

    auto sensorFactory = ImuFactory(bmp, hmc, mpu);
    ImuSensor subSensors(sensorFactory, scriptLogger);

    auto imuP = ImuPower(mpu, hmc, bmp);
    auto ep = EscPower(serial);
    auto pm = PowerManager(ep, imuP);
    auto lights = Headlights(serial);

    CommandDispatcher cd(std::cin, tc, pm, lights, subSensors);
    std::cout << "Ready!\n";
    cd.runLoop();

    return 0;

}
