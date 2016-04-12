/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#ifndef _TCP_SERVER_
#define _TCP_SERVER_

#include <iostream>
#include <string>
#include "ISocket.h"
#include "SocketServer.h"

class TcpServer : public ISocket
{
	static const unsigned int RCV_BUF_SIZE = 64;

public:
	TcpServer(int port);

	virtual ~TcpServer();

	int connect();

	void disconnect();

	void operator >> (std::string &val);

	void operator << (std::string val);

private:
	int port_;
	TCPSocket *socket;
	bool connected;
};

#endif