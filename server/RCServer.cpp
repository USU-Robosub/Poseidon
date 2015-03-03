
#include <RCServer.hpp>
#include <netdb.h>
#include <unistd.h>
#include <iostream>


RCServer::RCServer(int port)
{
    std::cout << "RC Server: initializing..." << std::endl;

    struct sockaddr_in serv_addr;
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    // set socket properties
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    // Initialize and start the socket
    bind(listenfd_, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd_, 10);

    std::cout << "RC Server: done" << std::endl;
}



void RCServer::start()
{
    char* ioBuff = new char[IO_BUFF_LEN];
    memset(ioBuff, 0, IO_BUFF_LEN);

    std::cout << "RC Server: listening..." << std::endl;

    // receive incoming connection
    int connfd = accept(listenfd_, NULL, NULL);

    std::cout << "RC Server: accepted" << std::endl;

    std::string input;

    do
    {
        // read data from client
        auto len = read(connfd, ioBuff, IO_BUFF_LEN);
        std::string input(ioBuff, len);

        std::cout << "RC Server: received " << len << std::endl;
        std::cout << input << std::endl;

        // do something
        // ioBuff = data array
        // IO_BUFF_LEN = size of array

        // write data back to client
        std::string res("result");
        memcpy(ioBuff, res.c_str(), res.size() + 1);
        write(connfd, ioBuff, res.size() + 1);

        // continue to read and write until '-1' is received
    } while (input != "close");

    // close connection and repeat
    close(connfd);
    delete ioBuff;
    sleep(10);
}
