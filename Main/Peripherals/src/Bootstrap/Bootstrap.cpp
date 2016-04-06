//
// Created by Nathan Copier on 11/10/2015.
//

#include <iostream>
#include <cstring>
#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"
#include <Headlights.h>
#include <TcpClient.h>
#include <map>

std::map<string, int> _createPortMap(int argCount, char** arguments);
std::pair<std::string, int> _getPort(char* portString);

int main(int argCount, char** arguments) {
    auto portMap = _createPortMap(argCount, arguments);

    auto loggerSocket = new TcpClient(portMap["loggerPort"]);
    auto scriptLogger = std::make_shared<ScriptLogger>(loggerSocket);
    auto serial = Serial();

    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, scriptLogger);

    auto pm = PowerManager();

    auto lights = Headlights(serial);

    auto dispatcherSocket = std::make_shared<TcpClient>(portMap["thrusterPort"]);
    CommandDispatcher cd(*dispatcherSocket, tc, pm, lights);
    cd.runLoop();

    return 0;

}

std::map<string, int> _createPortMap(int argCount, char** arguments) {
    auto portMap = std::map<string, int>();
    for(auto i = 1; i < argCount; i++) {
        portMap.insert(_getPort(arguments[i]));
    }
    return portMap;
}

std::pair<std::string, int> _getPort(char* portString) {
    auto argString = string(portString);
    int portPosition = argString.find('=');
    auto portName = argString.substr(2,portPosition-2);
    auto portAddress = atoi(argString.substr(portPosition+1).c_str());
    return make_pair(portName, portAddress);
}
