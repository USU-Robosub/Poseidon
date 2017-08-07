#include "TerminalLogger.hpp"

void TerminalLogger::update(IHub* hub){

}

void TerminalLogger::process(IHub* hub, std::string connection, json message){
  if(message["target"] == nodeName){
    if(message["type"] == "LOG"){
      std::cout << "[LOG] " << message["data"] << std::endl;
    }else if(message["type"] == "WARNING"){
      std::cout << "[WARNING] " << message["data"] << std::endl;
    }else if(message["type"] == "ERROR"){
      std::cout << "[ERROR] " << message["data"] << std::endl;
    }
  }else{
    std::cout << "[MESSAGE] " << message << std::endl;
  }
}
