#include "Message.hpp"

Message::Message(){
  this->target = "";
  this->type = "";
  this->sender = "";
  this->data = json();
}

Message& Message::to(std::string target){
  this->target = target;
  hasTarget = true;
  return *this;
}

Message& Message::ofType(std::string type){
  this->type = type;
  hasType = true;
  return *this;
}

Message& Message::from(std::string sender){
  this->sender = sender;
  hasSender = true;
  return *this;
}

Message& Message::withData(json data){
  this->data = data;
  hasData = true;
  return *this;
}

Message& Message::withNoData(){
  this->data = json({});
  hasData = true;
  return *this;
}

Message::Message(std::string jsonString){
  try{
    json parsedMessage = json::parse(jsonString);
    if(parsedMessage["target"].is_null() ||
        parsedMessage["type"].is_null() ||
        parsedMessage["sender"].is_null() ||
        parsedMessage["data"].is_null()) {
      target = type = sender = "";
      data = json::object();
    }else{
      target = parsedMessage["target"];
      type = parsedMessage["type"];
      sender = parsedMessage["sender"];
      data = parsedMessage["data"];
      hasTarget = hasType = hasSender = hasData = true;
    }
  }catch(...){
    target = type = sender = "";
    data = json::object();
  }
}

Message::Message(std::string target, std::string type, std::string sender){
  this->target = target;
  this->type = type;
  this->sender = sender;
  this->data = json({});
  hasTarget = hasType = hasSender = hasData = true;
}

Message::Message(std::string target, std::string type, std::string sender, json data){
  this->target = target;
  this->type = type;
  this->sender = sender;
  this->data = data;
  hasTarget = hasType = hasSender = hasData = true;
}

bool Message::isAddressedTo(std::string target){
  return this->target == target;
}

bool Message::matchesType(std::string type){
  return this->type == type;
}

bool Message::isFrom(std::string sender){
  return this->sender == sender;
}

bool Message::isMalformed(){
  return !(hasTarget && hasType && hasSender && hasData);
}

std::string& Message::getTarget(){
  return target;
}

std::string& Message::getType(){
  return type;
}

std::string& Message::getSender(){
  return sender;
}

json& Message::getData(){
  return data;
}

std::string Message::toJsonString(){
  return json({
    {"target", target},
    {"type", type},
    {"sender", sender},
    {"data", data}
  }).dump();
}

bool Message::operator==(const Message message) const{
  return target == message.target &&
    type == message.type &&
    sender == message.sender &&
    data == message.data;
}

std::ostream& operator<<(std::ostream& os, const Message& message){
    os << message.target << '|' << message.type << '|' << message.sender << '|' << message.data;
    return os;
}
