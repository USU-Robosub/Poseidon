#ifndef MOCK_CONNECTION_H
#define MOCK_CONNECTION_H

#include "gmock/gmock.h"
#include "Connection.hpp"

class MockConnection : public Connection{
public:
  MOCK_METHOD1(send, void(std::string));
  MOCK_METHOD0(read, std::queue<std::string>());
};

#endif
