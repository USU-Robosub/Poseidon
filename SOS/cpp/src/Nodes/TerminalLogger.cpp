#include "TerminalLogger.hpp"

void TerminalLogger::update(IHub* hub){

}

void TerminalLogger::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName)){
    if(message->matchesType("LOG")){
      std::cout << "[LOG] " << message->getData() << std::endl;
    }else if(message->matchesType("WARNING")){
      std::cout << "[WARNING] " << message->getData() << std::endl;
    }else if(message->matchesType("ERROR")){
      std::cout << "[ERROR] " << message->getData() << std::endl;
    }
  }else{
    std::cout << "[MESSAGE] " << message << std::endl;
  }
}
