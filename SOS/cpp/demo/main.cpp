#include "Hub.hpp"
#include "SOS.hpp"
#include "TerminalLogger.hpp"
#include <iostream>

class Terminal : public Connection {
  void send(std::string message){
    std::cout << "[TERMINAL] Message received " << message << std::endl;
  }

  std::queue<std::string> read(){
    std::queue<std::string> messages;
    std::string target, type, data;
    std::cout << "[TERMINAL] - Terminal Input -" << std::endl;
    std::cout << "[TERMINAL] Target: ";
    std::getline(std::cin, target);
    std::cout << "[TERMINAL] Type: ";
    std::getline(std::cin, type);
    std::cout << "[TERMINAL] Data: ";
    std::getline(std::cin, data);
    messages.push(json({
      {"target", target},
      {"type", type},
      {"from", "Terminal"},
      {"data", json::parse(data)}
    }).dump());
    std::cout << "[TERMINAL] Sending " << messages.front() << std::endl;
    return messages;
  }
};

int main(int argCount, char** arguments) {

  Hub app("SOS demo");

  SOS sos;
  TerminalLogger logger;
  sos.becomeMaster(&logger);
  sos.runOn(&app);

  //app.use("ACTUATOR_LOCK", new ActuatorLock(generateUUID)); // <- only on one hub in network, must be named ACTUATOR_LOCK
  //app.use("ActionSwitch", new DebouncedButton(12)); // ([pin on beaglebone])
  //app.use("Heading", new CompassNode(32)); // ([pin on beaglebone])
  //app.use("Move", new SpeedAndHeadingNode("Heading", "TankMove", 1, 0.2, 2)); // ([polled heading sensor's node name], [driven tank drive node name], [P], [I], [D])
  //app.use("TankMove", new TankDriveNode("LeftThrustMotor", "RightThrustMotor", -1, -0.1, 0.1, 1)); // ([left motor], [right motor], [max negative thrust], [min negative thrust], [min positive thrust], [max positive thrust])
  //app.use("Dive", new DualDiveNode("FrontDiveMotor", "BackDiveMotor", -1, -0.1, 0.1, 1)); // ([dive motor1], [dive motor2], [max negative thrust], [min negative thrust], [min positive thrust], [max positive thrust])

   // allows for nodes on this hub to talk to other nodes on this hub
  //app.connect("LOCAL", new Loopback()); // <- must be named LOCAL
  //app.connect("Arduino", new SerialConnection("/dev/ttyACM0"));
  //app.connect("WebApp", new WebSocketConnection(1234)); // ([port number]) the web app could also connect to the brain, and then get its commands routed to this hub
  //app.connect("Brain", new SocketConnection(2345)); // ([port number])

  //
  app.send("LOCAL", "{\"target\": \"LOGGER\", \"type\": \"LOG\", \"data\": \"hellow world!!\"}");
  app.connect("Terminal", new Terminal);

  app.listen(); // will hang until exit command is sent

  return 0;
}
