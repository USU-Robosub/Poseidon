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
  std::cout << "hello 1" << std::endl;
  shouldRead = true;
  while (shouldRead && !stream->eof()) {
    //std::cout << "hello 2" << std::endl;
    //std::getline(*stream, line);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto amount = stream->rdbuf()->in_avail();
    std::cout << "got line: " << amount << std::endl;
    //std::lock_guard<std::mutex> lock(mutex);
    //lines.push(line);
  }
}

void NonblockingStream::stopAfterNextLine(){
  shouldRead = false;
  //std::istringstream oss("testdata\n");
  //stream->rdbuf(oss.rdbuf()); //force a line to be added
  std::cout << "force close" << std::endl;
  thread->join();
  delete thread;
}

bool NonblockingStream::canRead(){
  return shouldRead;
}
