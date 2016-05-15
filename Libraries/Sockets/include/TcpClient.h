/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#ifndef _TCP_CLIENT_
#define _TCP_CLIENT_

#include <streambuf>
#include <stdio.h>
#include <string>
#include "SocketServer.h"

class TcpClient : private std::streambuf, public iostream
{
	static const unsigned int BUF_SIZE = 256;
	char* outputBuffer_;
	char* inputBuffer_;
    TCPSocket *socket;

	int connect_(int port, std::string address);

public:
	TcpClient(int port, std::string address = "127.0.0.1");
	void disconnect();
    int sync();
    int underflow();
	virtual ~TcpClient();
};

#endif