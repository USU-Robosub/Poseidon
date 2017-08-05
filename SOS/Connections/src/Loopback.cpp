#include "Loopback.hpp"

void Loopback::send(std::string message){
  messages.push(message);
}

std::queue<std::string> Loopback::read(){
  std::queue<std::string> receivedMessages;
  while(!messages.empty()){
    receivedMessages.push(messages.front());
    messages.pop();
  }
  return receivedMessages;
}
