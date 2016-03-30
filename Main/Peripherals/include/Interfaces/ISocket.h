/**
  *	Created by TekuConcept on Mar 29, 2016
  */

#ifndef _ISOCKET_
#define _ISOCKET_

#include <string>

class ISocket {
public:
	virtual int connect() = 0;
	virtual void operator >> (std::string & buffer) = 0;
	virtual void operator << (std::string buffer) = 0;
};

#endif