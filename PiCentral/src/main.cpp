#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <tacopie/tacopie>

#include "GateDetector.hpp"

bool is_number(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int main(int argc, char** argv) {
	
	if(argc != 5) {
		std::cout << "Invalid number of arguments to " << argv[0] << std::endl;
		std::cout << "Usage: <address> <port> <camera_file_path | camera_number> <template_image_url>" << std::endl;
		return 1;
	}
	
	std::string address = argv[1];
	std::uint32_t port = std::stoi(argv[2]);
	std::string camera_source = argv[3];
	std::string template_image_url = argv[4];
	
	tacopie::tcp_client client;
	client.connect(address, port);
	
	GateDetector gd;
	if(is_number(camera_source)) {
		auto camera_number = std::stoi(camera_source);
		gd.start(camera_number);
	} else {
		gd.start(camera_source);
	}
	
    return 0;
}
