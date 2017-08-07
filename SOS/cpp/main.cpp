#include "Hub.hpp"
#include "SOS.hpp"

int main(int argCount, char** arguments) {

  Hub app("Peripherals");

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

  SOS sos(true);
  sos.runOn(app);

  app.listen(); // will hang until exit command is sent

  return 0;
}
