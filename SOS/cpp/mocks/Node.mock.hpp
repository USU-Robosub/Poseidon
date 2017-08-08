#ifndef MOCK_NODE_H
#define MOCK_NODE_H

#include "gmock/gmock.h"
#include "Node.hpp"

class MockNode : public Node{
public:
  MOCK_METHOD1(setName, void(std::string));
  MOCK_METHOD1(update, void(IHub*));
  MOCK_METHOD3(process, void(IHub*, std::string, json));
};

#endif
