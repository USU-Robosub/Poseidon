#include <string>
#include "Hub.hpp"
#include "ActuatorLock.hpp"
#include "Loopback.hpp"
#include "PseudoGUID.hpp"

int main(int argCount, char** arguments) {
  std::string name = "Peripherals";
  Hub app(name);

  app.address("Arduino", "LeftThrustMotor"); // <- if LeftThrustMotor is needed ask Arduino
  app.address("Arduino", "RightThrustMotor");
  app.address("Arduino", "FrontDiveMotor");
  app.address("Arduino", "BackDiveMotor");

  app.use("ACTUATOR_LOCK", new ActuatorLock(generateUUID)); // <- only on one hub in network, must be named ACTUATOR_LOCK
  //app.use("ActionSwitch", new DebouncedButton(12)); // ([pin on beaglebone])
  //app.use("Heading", new CompassNode(32)); // ([pin on beaglebone])
  //app.use("Move", new SpeedAndHeadingNode("Heading", "TankMove", 1, 0.2, 2)); // ([polled heading sensor's node name], [driven tank drive node name], [P], [I], [D])
  //app.use("TankMove", new TankDriveNode("LeftThrustMotor", "RightThrustMotor", -1, -0.1, 0.1, 1)); // ([left motor], [right motor], [max negative thrust], [min negative thrust], [min positive thrust], [max positive thrust])
  //app.use("Dive", new DualDiveNode("FrontDiveMotor", "BackDiveMotor", -1, -0.1, 0.1, 1)); // ([dive motor1], [dive motor2], [max negative thrust], [min negative thrust], [min positive thrust], [max positive thrust])

  app.connect(name, new Loopback()); // <- allows for nodes on this hub to talk to other nodes on this hub
  //app.connect("Arduino", new SerialConnection("/dev/ttyACM0"));
  //app.connect("WebApp", new WebSocketConnection(1234)); // ([port number]) the web app could also connect to the brain, and then get its commands routed to this hub
  //app.connect("Brain", new SocketConnection(2345)); // ([port number])

  app.listen(); // will hang until exit command is sent
  
  return 0;
}
