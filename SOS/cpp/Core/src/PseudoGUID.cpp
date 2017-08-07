#include "PseudoGUID.hpp"

std::string generateUUID(){
  return chr8() + '-' + chr4() + '-' + chr4() + '-' + chr4() + '-' + chr12();
}

std::string chr12(){
  return endSlice("00000000000000" + toHex(std::time(nullptr)), 12);
}

std::string chr8(){
  return chr4() + chr4();
}

std::string chr4(){
  return endSlice(toHex(rand()), 4);
}

std::string toHex(int value){
  std::stringstream stream;
  stream << std::hex << value;
  return stream.str();
}

std::string endSlice(std::string value, unsigned int length){
  return value.substr(value.length() - length, value.length());
}
