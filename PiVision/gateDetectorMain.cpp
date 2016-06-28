#include <GateDetector.h>
#include <TcpClient.h>

int main(int argc, char** args) {
    GateDetector gd;
    if (argc <= 2) {
        gd.startThreads(std::cin, std::cout);
    }
    else {
        auto port = std::atoi(args[1]);
        auto address = args[2];
        std::cout << "Port: " << port << "\nAddress: " << address << std::endl;
        auto socket = new TcpClient(port, address);
        gd.startThreads(*socket, *socket);
        socket->disconnect();
        delete(socket);
    }
}
