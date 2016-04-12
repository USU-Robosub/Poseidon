/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#ifndef _TCP_CLIENT_
#define _TCP_CLIENT_

#include <iostream>
#include <string>
#include "ISocket.h"
#include "SocketServer.h"

class TcpClient : public ISocket
{
	static const unsigned int RCV_BUF_SIZE = 64;

public:
	TcpClient(int port, std::string address = "0.0.0.0");
	
	virtual ~TcpClient();

	int connect();
	
	void operator >> (std::string & val);

	void operator << (std::string val);

private:
	int port_;
	std::string address_;
	TCPSocket *socket;
};

#endif