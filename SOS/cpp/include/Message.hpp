#ifndef MESSAGE_H
#define MESSAGE_H

#include <ostream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Message{
public:
  Message();
  Message(std::string jsonString);
  Message(std::string target, std::string type, std::string sender);
  Message(std::string target, std::string type, std::string sender, json data);
  Message& to(std::string target);
  Message& ofType(std::string type);
  Message& from(std::string sender);
  Message& withData(json data);
  Message& withNoData();
  bool isAddressedTo(std::string target);
  bool matchesType(std::string type);
  bool isFrom(std::string sender);
  bool isMalformed();
  std::string& getTarget();
  std::string& getType();
  std::string& getSender();
  json& getData();
  std::string toJsonString();
  bool operator==(const Message message) const;
  friend std::ostream& operator<<(std::ostream& os, const Message& message);
private:
  bool hasTarget = false, hasType = false, hasSender = false, hasData = false;
  std::string target, type, sender;
  json data;
};

#endif
