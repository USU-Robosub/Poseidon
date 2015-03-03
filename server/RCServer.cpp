
#include <RCServer.hpp>
#include <netdb.h>
#include <unistd.h>


RCServer::RCServer(int port)
{
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
}



void RCServer::start()
{
    char* ioBuff = new char[IO_BUFF_LEN];
    memset(ioBuff, 0, IO_BUFF_LEN);

    // receive incoming connection
    int connfd = accept(listenfd_, NULL, NULL);

    do
    {
        // read data from client
        read(connfd, ioBuff, IO_BUFF_LEN);

        // do something
        // ioBuff = data array
        // IO_BUFF_LEN = size of array

        // write data back to client
        write(connfd, ioBuff, IO_BUFF_LEN);

        // continue to read and write until '-1' is received
    } while (true);

    // close connection and repeat
    close(connfd);
    delete ioBuff;
    sleep(10);
}
