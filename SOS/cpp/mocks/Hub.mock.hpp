#ifndef MOCK_HUB_H
#define MOCK_HUB_H

#include "gmock/gmock.h"
#include "Hub.hpp"

class DummyHub : public Hub{
public:
  DummyHub() : Hub("DummyHub") {}
  void send(std::string, Message){
    throw std::logic_error("Dummy method called");
  }
  void use(std::string, Node*){
    throw std::logic_error("Dummy method called");
  }
  void connect(std::string, Connection*){
    throw std::logic_error("Dummy method called");
  }
  void listen(){
    throw std::logic_error("Dummy method called");
  }
  void setLogger(std::string, std::string){
    throw std::logic_error("Dummy method called");
  }
  void logError(std::string){
    throw std::logic_error("Dummy method called");
  }
  std::string getName(){
    throw std::logic_error("Dummy method called");
  }
  std::vector<std::string> getNodeNames(){
    throw std::logic_error("Dummy method called");
  }
  std::vector<std::string> getConnectionNames(){
    throw std::logic_error("Dummy method called");
  }
  void exit(){
    throw std::logic_error("Dummy method called");
  }
};

class MockHub : public Hub{
public:
  MockHub() : Hub("MockHub") {}
  MOCK_METHOD2(send, void(std::string, Message));
  MOCK_METHOD2(use, void(std::string, Node*));
  MOCK_METHOD2(connect, void(std::string, Connection*));
  MOCK_METHOD2(setLogger, void(std::string, std::string));
  MOCK_METHOD1(logError, void(std::string));
  MOCK_METHOD0(listen, void());
  MOCK_METHOD0(getName, std::string());
  MOCK_METHOD0(getNodeNames, std::vector<std::string>());
  MOCK_METHOD0(getConnectionNames, std::vector<std::string>());
  MOCK_METHOD0(exit, void());
};

#endif
