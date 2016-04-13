//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"
#include "EscPower.h"
#include <Headlights.h>
#include <TcpClient.h>
#include <map>
#include <MPU6050.h>
#include <HMC5883L.h>
#include <BMP085.h>
#include <ImuPower.h>
#include <ImuFactory.h>

std::ostream* _getOutputStream(std::map<std::string, int>& portMap, string portName);
std::istream* _getInputStream(std::map<std::string, int>& portMap, string portName);
std::map<std::string, int> _createPortMap(int argCount, char** arguments);
std::pair<std::string, int> _getPort(char* portString);

int main(int argCount, char** arguments) {
    auto portMap = _createPortMap(argCount, arguments);

    auto loggerStream = _getOutputStream(portMap, "loggerPort");
    auto scriptLogger = std::make_shared<ScriptLogger>(loggerStream);
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

    auto dispatcherStream = _getInputStream(portMap, "thrusterPort");
    CommandDispatcher cd(*dispatcherStream, tc, pm, lights, subSensors);
    scriptLogger->info("Ready!");
    cd.runLoop();

    return 0;
}

std::ostream* _getOutputStream(std::map<std::string, int>& portMap, string portName) {
    std::ostream* out;
    if(portMap.count(portName)) out = new TcpClient(portMap[portName]);
    else out = &(std::cout);
    return out;
}

std::istream* _getInputStream(std::map<std::string, int>& portMap, string portName) {
    std::istream* in;
    if(portMap.count(portName)) in = new TcpClient(portMap[portName]);
    else in = &(std::cin);
    return in;
}

std::map<std::string, int> _createPortMap(int argCount, char** arguments) {
    auto portMap = std::map<string, int>();
    for(auto i = 1; i < argCount; i++) {
        portMap.insert(_getPort(arguments[i]));
    }
    return portMap;
}

std::pair<std::string, int> _getPort(char* portString) {
    auto argString = string(portString);
    int portPosition = (int)argString.find('=');
    auto portName = argString.substr(2, (unsigned long)(portPosition - 2));
    auto portAddress = atoi(argString.substr((unsigned long)(portPosition + 1)).c_str());
    return make_pair(portName, portAddress);
}
