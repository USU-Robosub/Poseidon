#include <string>
#include <cstdint>
#include <iostream>
#include <tacopie/tacopie>

int main(int argc, char** argv) {
	
	if(argc != 6) {
		std::cout << "Invalid number of arguments to " << argv[0] << std::endl;
		std::cout << "Usage: <address> <port> <camera_file_path> <camera_number> <template_image_url>" << std::endl;
		return 1;
	}
	
	std::string address = argv[1];
	std::uint32_t port = std::stoi(argv[2]);
	std::string camera_file_path = argv[3];
	std::uint32_t camera_number = std::stoi(argv[4]);
	std::string template_image_url = argv[5];
	
	tacopie::tcp_client client;
	client.connect(address, port);
	
    return 0;
}
