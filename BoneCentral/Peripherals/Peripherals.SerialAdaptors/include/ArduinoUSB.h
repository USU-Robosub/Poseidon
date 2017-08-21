#ifndef ARDUINO_USB_H
#define ARDUINO_USB_H

#include <string>
#include "Serial.h"
#include "Node.hpp"

using json = nlohmann::json;

class ArduinoUSB : public Node{
public:
  ArduinoUSB(std::string USBport) : serial(USBport) {}
  void update(IHub* hub);
  void process(IHub* hub, std::string* connection, Message* message);
private:
  Serial serial;
};

#endif
