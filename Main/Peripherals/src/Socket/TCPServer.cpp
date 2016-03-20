/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "SocketServer.h"  // For Socket, ServerSocket, and SocketException
#include <iostream>           // For cerr and cout
#include <cstdlib>            // For atoi()

#include <ThrustController.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"
#include <Headlights.h>

using namespace std;
const unsigned int RCVBUFSIZE = 64;    // Size of receive buffer
int HandleTCPClient(TCPSocket *sock, CommandDispatcher &cd); // TCP client handling function
CommandDispatcher* InitBootstrap();



int main(int argc, char *argv[]) {
  if (argc != 2) {                     // Test for correct number of arguments
    cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
    exit(1);
  }

  cout << "Listening on port " << argv[1] << endl;
  unsigned short echoServPort = atoi(argv[1]);  // First arg: local port

  try {
    TCPServerSocket servSock(echoServPort);     // Server Socket object
    
    
    auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
    auto serial = Serial();
    auto thrusterFactory = SerialThrusterFactory(serial);
    ThrustController tc(thrusterFactory, scriptLogger);
    auto pm = PowerManager();
    auto lights = Headlights(serial);
    CommandDispatcher cd(tc, pm, lights);
    //CommandDispatcher *cd = InitBootstrap();
    
    for (;;) {   // Run forever
      if(HandleTCPClient(servSock.accept(), cd)) // Wait for a client to connect
      {
        break;
      }
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }

  return 0;
}



// TCP client handling function
int HandleTCPClient(TCPSocket *sock, CommandDispatcher &dispatcher) {
  cout << "Handling client ";
  try { cout << sock->getForeignAddress() << ":"; }
  catch (SocketException e) { cerr << "Unable to get foreign address" << endl; }
  try { cout << sock->getForeignPort(); }
  catch (SocketException e) { cerr << "Unable to get foreign port" << endl; }
  cout << endl;
  
  char buffer[RCVBUFSIZE];
  stringstream ss;
  int recvMsgSize, shouldExit = 0; // zero means end of transmission
  while ((recvMsgSize = sock->recv(buffer, RCVBUFSIZE)) > 0) {
    // set nullterminator
    int max_idx = (recvMsgSize==RCVBUFSIZE?RCVBUFSIZE-1:recvMsgSize);
    buffer[max_idx] = '\0';
    fprintf(stderr, "%s", buffer);
    
    ss.write(buffer, recvMsgSize-1);
    if(!dispatcher.run(ss))
    {
      fprintf(stderr,"Exiting...\n");
      shouldExit = 1;
      break;
    }
    ss.clear();
  }
  
  delete sock;
  return shouldExit;
}



CommandDispatcher* InitBootstrap() {
  auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
  auto serial = Serial();
  auto thrusterFactory = SerialThrusterFactory(serial);
  ThrustController tc(thrusterFactory, scriptLogger);
  auto pm = PowerManager();
  auto lights = Headlights(serial);
  return new CommandDispatcher(tc, pm, lights);
}