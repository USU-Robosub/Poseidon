//
// Created by Nathan Copier on 11/10/2015.
//

#include "Assembler.h"

void App_Start(int argCount, char **arguments) {
    // gets ports by command line
    auto portMap = _createPortMap(argCount, arguments);

    // Message transfer system
    Hub app("Peripherals");

    // basic SOS nodes
    SOS sos;
    sos.becomeMaster(new TerminalLogger);
    sos.runOn(&app);

    // Old Javascript <-> C++ TCP protocol to SOS commands
    CommandDispatcherConverter commandDispatcher(
      "127.0.0.1",
      portMap["dispatcherPort"],
      "MoveThruster",
      "YawPID",
      "DiveThruster",
      "",/*std::string escSwitchName,*/
      "",/*std::string lightSwitchName,*/
      "",/*std::string accelerometerName,*/
      "",/*std::string gyroscopeName,*/
      "",/*std::string compassName,*/
      "",/*std::string internalTemperatureName,*/
      "",/*std::string internalPressureName,*/
      "",/*std::string externalTemperatureName,*/
      ""/*std::string externalPressureName*/
    );
    app.use("CommandDispatcher", &commandDispatcher);

    //app.use(/*i2c converter*/);

    // SOS commands to USB serial to Arduino
    ArduinoUSB arduinoUSB("/dev/ttyACM0");
    app.use("Arduino", &arduinoUSB);

    // PID controller for yaw
    PIDnode yawPID("Heading", "Yaw", 0, 0, 0, 0);
    app.use("yawPID", &yawPID);

    // Arduino thrusters
    Thruster moveThruster("Arduino", MOVE_IDX);
    Thruster yawThruster("Arduino", YAW_IDX); // why is yaw a thruster ?
    Thruster diveThruster("Arduino", DIVE_IDX);
    app.use("MoveThruster", &moveThruster);
    app.use("DiveThruster", &diveThruster);
    app.use("YawThruster", &yawThruster);

    // For testing
    //TCPserver brain("127.0.0.1", portMap["dispatcherPort"]);
    //app.connect("Brain", &brain);

    app.listen();
    /*
    Pid yawPid(target, P, I, D, [](IHub* hub){get value}, [](IHub* hub){set value});
    */

    /*
    CommandDispatcherConverter commandConverter(inputStream, outputStream,
      "MoveThruster", "DiveThruster", "YawThruster",
    );
    */

    //app.connect(/*node tcp*/); /* or */ app.connect(/*terminal*/);
    //app.connect(/*beaglebone i2c*/);
    //app.connect(/*arduino usb serial*/);

    /*
    // connection : dispatcher(TCP) or terminal(CIN|COUT)
    auto dispatcherStream = _getSocketStream(portMap, "dispatcherPort");
    std::istream& inputStream = dispatcherStream ? *dispatcherStream : std::cin;
    std::ostream& outputStream = dispatcherStream ? *dispatcherStream : std::cout;

    // connection : i2c
    auto i2CFactory = I2CFactory();
    // connection : serial(USB_Arduino)
    auto serialFactory = SerialFactory(outputStream);
    auto powerFactory = PowerFactoryAdaptor(i2CFactory, serialFactory);
    auto sensorFactory = SensorFactoryAdaptor(i2CFactory, serialFactory);

    // connection : logger(TCP) or terminal(COUT)
    auto loggerStream = _getSocketStream(portMap, "loggerPort");
    auto scriptLogger = std::make_shared<ScriptLogger>(loggerStream ? *loggerStream : std::cout);

    ImuSensor subSensors(sensorFactory, scriptLogger);
    ThrustController tc(serialFactory, subSensors, scriptLogger);
    auto pm = PowerManager(powerFactory);
    auto lights = serialFactory.createHeadlights();
    //CommandDispatcher cd(inputStream, outputStream, subSensors, tc, pm, *lights, *scriptLogger);
    auto arduinoAction = serialFactory.createArduinoAction();

    arduinoAction->setEdge(ActionThread::EdgeMode::BOTH);
    arduinoAction->begin();
    scriptLogger->info("Ready!");
    //cd.runLoop();
    if(dispatcherStream) dispatcherStream->disconnect();
    std::cout << "\n- End of Line -\n";
    */
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
