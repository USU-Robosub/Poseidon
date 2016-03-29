#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include <ThrustController.h>
#include <Headlights.h>
#include <CommandDispatcher.h>
#include "SerialThrusterFactory.h"
#include "ScriptLogger.h"

#include "TcpServer.h"

int main() {
	const int PORT = 5040;
	std::cout << "Listening on port " << PORT << std::endl;

	// setup bootstrap
	auto scriptLogger = std::make_shared<ScriptLogger>(&std::cout);
	auto serial = Serial();
	auto thrusterFactory = SerialThrusterFactory(serial);
	ThrustController tc(thrusterFactory, scriptLogger);
	auto pm = PowerManager();
	auto lights = Headlights(serial);
	CommandDispatcher cd(tc, pm, lights);

	// setup sockets
	TcpServer server(PORT);
	server.connect();

	std::string command;
	std::stringstream ss;
	while (true) {
		server >> command;
		if(command.at(0) == '\0')
			break;

		ss << command;
		if(!cd.run(ss))
			break;
		ss.clear();
	}

	return 0;
}