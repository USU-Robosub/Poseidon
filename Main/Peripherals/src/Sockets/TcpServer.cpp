/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#include "TcpServer.h"

TcpServer::TcpServer(int port) :
	port_(port), socket(NULL), connected(false) {}



TcpServer::~TcpServer() {
	std::cout << "Tearing down server..." << std::endl;
	if(socket != NULL)
		delete socket;
}



int TcpServer::connect() {
	disconnect(); // close open connections
	TCPServerSocket serverSock(port_);
	try {
		socket = serverSock.accept();
		connected = true;
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}



void TcpServer::disconnect() {
	connected = false;
	if(socket != NULL)
		delete socket;
}



void TcpServer::operator >> (std::string &val) {
	if(connected)
		try {
			int recvMsgSize = 0;
			char buffer[RCV_BUF_SIZE];
			recvMsgSize = socket->recv(buffer, RCV_BUF_SIZE);
			std::string line(buffer, recvMsgSize);
			val = line;
		} catch (SocketException &e) {
			std::cerr << e.what() << std::endl;
			val = "\0";
		}
	else
		val = "\0";
}



void TcpServer::operator << (std::string val) {
	if(connected)
		try {
			int w_size = val.length();
			if(w_size > 0)
				socket->send(val.c_str(), w_size);
		} catch (SocketException &e) {
			std::cerr << e.what() << std::endl;
		}
}