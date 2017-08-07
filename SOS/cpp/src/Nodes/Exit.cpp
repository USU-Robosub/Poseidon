#include "Exit.hpp"

void Exit::update(IHub* hub){

}

void Exit::process(IHub* hub, std::string connection, json message){
  if(message["type"] == "EXIT"){
    hub->exit();
  }
}
