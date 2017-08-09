#ifndef ARDUINO_USB_H
#define ARDUINO_USB_H

#include <string>
#include "Node.hpp"

class ArduinoUSB : public Node{
public:
  ArduinoUSB(std::string USBport) : serial(USBport) {}
  void update(IHub* hub);
  void process(IHub* hub, std::string connection, json message);
private:
  std::string generate_GOT(std::string target, json value);
  Serial serial;
};

#endif
