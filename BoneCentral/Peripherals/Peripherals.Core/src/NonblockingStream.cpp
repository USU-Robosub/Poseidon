#include "NonblockingStream.h"

bool NonblockingStream::hasLine(){
  std::lock_guard<std::mutex> lock(mutex);
  return !lines.empty();
}

std::string NonblockingStream::readLine(){
  std::lock_guard<std::mutex> lock(mutex);
  if (lines.empty()) { return ""; }
  auto line = lines.front();
  lines.pop();
  return line;
}

void NonblockingStream::threadEntry(){
  std::string line;
  while (shouldRead) {
    std::getline(std::cin, line)
    std::lock_guard<std::mutex> lock(mutex);
    lines.push(line);
  }
}

void NonblockingStream::stopAfterNextLine(){
  std::lock_guard<std::mutex> lock(mutex);
  shouldRead = false;
  thread.join();
}

bool canRead(){
  return shouldRead;
}
