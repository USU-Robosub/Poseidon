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
    messages.push(Message(target, type, "Terminal", json::parse(data)).toJsonString());
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

  app.connect("Terminal", new Terminal);

  app.listen(); // will hang until exit command is sent

  return 0;
}
