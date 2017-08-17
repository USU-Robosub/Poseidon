#include "Exit.hpp"

void Exit::update(IHub*){

}

void Exit::process(IHub* hub, std::string* connection, Message* message){
  if(message->isAddressedTo(nodeName) && message->matchesType("EXIT")){
    hub->exit();
  }
}
