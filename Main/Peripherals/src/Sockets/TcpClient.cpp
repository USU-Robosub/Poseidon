/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#include "TcpClient.h"

TcpClient::TcpClient(int port, std::string address) :
{
	connect_(port, address);
}



TcpClient::~TcpClient() {
	std::cout << "Tearing down Client...\n";
	if(socket != NULL)
		delete socket;
}



int TcpClient::connect_(int port, std::string address) {
	try {
		socket = new TCPSocket(address, port);
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}


	
void TcpClient::operator >> (std::string &val) {
	try {
		int received = 0;
		char buffer[RCV_BUF_SIZE];
		if((received = socket->recv(buffer, RCV_BUF_SIZE)) <= 0) {
			std::cerr << "Unable to read";
			val = "\0";
		}
		int max = received == RCV_BUF_SIZE ? RCV_BUF_SIZE-1 : received;
		buffer[max] = '\0';
		val = buffer;
	} catch (SocketException &e) {
		std::cerr << e.what() << std::endl;
		val = "\0";
	}
}



void TcpClient::operator << (std::string val) {
	int strLen = std::strlen(val.c_str());
	if(strLen <= 0)
		return;
	if(socket != NULL) {
		try {
			socket->send(val.c_str(), strLen);
		} catch (SocketException &e) {
			std::cerr << e.what() << std::endl;
			return;
		}
	}
}