#ifndef PERIPHERALS_COMMAND_DISPATCHER_H
#define PERIPHERALS_COMMAND_DISPATCHER_H

#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <atomic>
#include <mutex>

class NonblockingStream {
public:
  AsyncStreamReader(std::istream* stream) : stream(stream) {
    _thread = std::thread([&] { threadEntry(); });
  }
  bool hasLine();
  bool canRead();
  std::string readLine();
  void stopAfterNextLine();
private:
  void threadEntry();
  bool shouldRead = false;
  std::istream* stream = nullptr;
  std::mutex mutex;
  std::queue<std::string> lines;
  std::thread thread;
};

#endif
