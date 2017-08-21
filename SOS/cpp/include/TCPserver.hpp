#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <sstream>
#include <tacopie/tacopie>
#include "Connection.hpp"

/*
Currently this TCP server is setup to only send to the last TCP client that connected
*/

class TCPserver : public Connection{
public:
  TCPserver(std::string host, unsigned int port);
  virtual void send(std::string message);
  virtual std::queue<std::string> read();
  virtual void setBufferSize(unsigned int bufferSize);
private:
  void onMessage(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res);
  bool lastMessageWasIncomplete = false;
  std::string incompleteMessage;
  std::queue<std::string> pendingMessages;
  std::queue<std::string> messages;
  tacopie::tcp_server server;
  unsigned int bufferSize = 1024;
};

#endif
