#include "Hub.hpp"

Hub::Hub(std::string name){

}

Hub::Hub(std::string name, std::string master){

}

void Hub::send(std::string hub, std::string node, std::string data){

}

void Hub::send(std::string node, std::string data){

}

void Hub::address(std::string hubName, std::string nodeName){

}

void Hub::use(std::string nodeName, Node* node){

}

void Hub::connect(std::string hubName, Connection* connection){

}

void Hub::listen(){

}

void Hub::softClose(){

}

void Hub::close(){

}

void Hub::error(std::string message){

}

void Hub::lock(std::string hub, std::string node){

}
