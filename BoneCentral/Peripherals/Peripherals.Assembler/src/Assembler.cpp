//
// Created by Nathan Copier on 11/10/2015.
//

#include "Assembler.h"

void App_Start(int argCount, char **arguments) {
    auto portMap = _createPortMap(argCount, arguments);

    auto i2CFactory = I2CFactory();
    auto serialFactory = SerialFactory();
    auto powerFactory = PowerFactoryAdaptor(i2CFactory, serialFactory);
    auto sensorFactory = SensorFactoryAdaptor(i2CFactory, serialFactory);

    auto loggerStream = _getSocketStream(portMap, "loggerPort");
    auto scriptLogger = std::make_shared<ScriptLogger>(loggerStream ? *loggerStream : std::cout);

    ThrustController tc(serialFactory, scriptLogger);
    ImuSensor subSensors(sensorFactory, scriptLogger);
    auto pm = PowerManager(powerFactory);
    auto lights = serialFactory.createHeadlights();

    auto dispatcherStream = _getSocketStream(portMap, "dispatcherPort");
    auto inputStream = dispatcherStream ? *dispatcherStream : std::cin;
    auto outputStream = dispatcherStream ? *dispatcherStream : std::cout;
    CommandDispatcher cd(inputStream, outputStream, subSensors, tc, pm, *lights);
    scriptLogger->info("Ready!");
    cd.runLoop();
    dispatcherStream->disconnect();
    std::cout << "\n- End of Line -\n";
}

TcpClient* _getSocketStream(std::map<std::string, int>& portMap, string portName) {
    if(!portMap.count(portName)) return NULL;
    return new TcpClient(portMap[portName]);
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
