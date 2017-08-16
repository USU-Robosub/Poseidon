//
// Created by Nathan Copier on 4/20/2016.
//

#ifndef PERIPHERALS_ASSEMBLER_START_H
#define PERIPHERALS_ASSEMBLER_H

#include <iostream>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "ScriptLogger.h"
#include "PowerFactoryAdaptor.h"
#include "SensorFactoryAdaptor.h"
#include <TcpClient.h>
#include <map>
#include "Hub.hpp"
#include "SOS.hpp"
#include "ArduinoUSB.h"
#include "Thruster.h"

TcpClient* _getSocketStream(std::map<std::string, int>& portMap, string portName);
std::map<std::string, int> _createPortMap(int argCount, char** arguments);
std::pair<std::string, int> _getPort(char* portString);

void App_Start(int argCount, char **arguments);

#endif //PERIPHERALS_ASSEMBLER_H
