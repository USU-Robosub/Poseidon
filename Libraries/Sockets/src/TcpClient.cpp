/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#include "TcpClient.h"

TcpClient::TcpClient(int port, std::string address) :
        std::iostream(this),
        outputBuffer_(new char[BUF_SIZE+1]),
        inputBuffer_(new char[BUF_SIZE+1]) {
    setp( outputBuffer_, outputBuffer_ + BUF_SIZE - 1 );
    setg( inputBuffer_, inputBuffer_ + BUF_SIZE - 1, inputBuffer_ + BUF_SIZE - 1 );
	connect_(port, address);
}

void TcpClient::disconnect() {
	if(socket != NULL) {
		socket->disconnect();
		socket = NULL;
	}
}



TcpClient::~TcpClient() {
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



int TcpClient::sync() {
    socket->send( pbase(), int(pptr() - pbase()) );
    setp(pbase(), epptr());
    return 0;
}

int TcpClient::underflow() {
    int bytesReceived = socket->recv(eback(), BUF_SIZE);
    setg(eback(), eback(), eback()+bytesReceived);
    return *eback();
}