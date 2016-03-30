/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#ifndef _TCP_CLIENT_
#define _TCP_CLIENT_

#include <iostream>
#include <string>
#include "SocketServer.h"

class TcpClient : public iostream
{
	static const unsigned int RCV_BUF_SIZE = 64;

	int connect_(int port, std::string address);

public:
	TcpClient(int port, std::string address = "0.0.0.0");
	
	virtual ~TcpClient();
	
	void operator >> (std::string& val);

	void operator << (std::string val);

private:
	TCPSocket *socket;
};

#endif