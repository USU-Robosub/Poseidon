#include "TCPserver.hpp"

TCPserver::TCPserver(std::string host, unsigned int port){
  server.start(host, port, [&] (const std::shared_ptr<tacopie::tcp_client>& client) -> bool {
    while(!pendingMessages.empty()){
      client->async_write({ std::vector<char>(pendingMessages.front().begin(), pendingMessages.front().end()), nullptr });
      pendingMessages.pop();
    }
    client->async_read({ bufferSize, std::bind(&TCPserver::onMessage, this, client, std::placeholders::_1) });
    return false;
  });
}

void TCPserver::send(std::string message){
  auto clients = server.get_clients();
  if(clients.size() > 0){
    clients.front()->async_write({ std::vector<char>(message.begin(), message.end()), nullptr });
  }else{
    pendingMessages.push(message);
  }
}

std::queue<std::string> TCPserver::read(){
  std::queue<std::string> messages;
  while(!this->messages.empty()){
    messages.push(this->messages.front());
    this->messages.pop();
  }
  return messages;
}

void TCPserver::setBufferSize(unsigned int bufferSize){
  this->bufferSize = bufferSize;
}

void TCPserver::onMessage(const std::shared_ptr<tacopie::tcp_client>& client, const tacopie::tcp_client::read_result& res){
  if (res.success) {
    // convert vector<chars> to string
    std::stringstream buffer;
    if(lastMessageWasIncomplete) buffer.str(incompleteMessage);
    for(int i = 0; i < res.buffer.size(); i++){ buffer << res.buffer[i]; }
    std::string data = buffer.str();
    // split messages apart between }|{
    size_t pos = 0;
    std::string message;
    while ((pos = data.find("}|{")) != std::string::npos) {
      message = data.substr(0, pos + 2);
      messages.push(message.substr(0, message.length() - 1));
      data.erase(0, pos + 2);
    }
    // try to check if buffer overflowed and the message is incomplete
    if(data.find("}|") == data.length() - 2){
      messages.push(data.substr(0, data.length() - 1));
    }else{
      lastMessageWasIncomplete = true;
      incompleteMessage = data;
    }
    // start another read pass
    client->async_read({ bufferSize, std::bind(&TCPserver::onMessage, this, client, std::placeholders::_1) });
  }
  else {
    client->disconnect();
  }
}
