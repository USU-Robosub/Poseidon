
#include <RCServer.hpp>
#include "../kernel/API/PowerManagement.h"
#include "../kernel/API/ThrustController.h"
#include "../kernel/API/IMUSensor.h"

#include <libs/jsoncpp-1.5.0/json/json.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>


RCServer::RCServer(int port):
    ioBuffer_(new char[IO_BUFF_LEN]),
    power_(std::make_shared<PowerManagement>()),
    thrust_(std::make_shared<ThrustController>()),
    imu_(std::make_shared<IMUSensor>())
{
    std::cout << "RC Server: initializing..." << std::endl;
    memset(ioBuffer_, 0, IO_BUFF_LEN);

    // set up socket
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



RCServer::~RCServer()
{
    delete ioBuffer_;
}



void RCServer::start()
{
    std::cout << "RC Server: listening..." << std::endl;

    while (true) //wait for new connections
    {
        // receive incoming connection
        int connfd = accept(listenfd_, NULL, NULL);

        std::cout << "RC Server: accepted" << std::endl;

        bool keepAlive = true;

        do
        {
            auto len = read(connfd, ioBuffer_, IO_BUFF_LEN); // read data from client
            keepAlive = process(connfd, std::string(ioBuffer_, len));

        } while (keepAlive);

        close(connfd); // close connection
        //sleep(10);
    }
}



bool RCServer::process(int connfd, const std::string& input)
{
    std::cout << "RC Server: received " << input << std::endl;

    Json::Value received(input);
    auto action = received.get("action", "UTF-8").asString();
    std::cout << action << std::endl;

    if (action == "enable power")
        power_->turnOnESCs();
    else if (action == "disable power")
        power_->turnOffESCs();
    else if (action == "set forward")
        thrust_->setForwardThrust(0.5);
    else if (action == "set drift")
        thrust_->setDriftThrust(0.5);
    else if (action == "set dive")
        thrust_->setDiveThrust(0.5);
    else if (action == "set yaw")
        thrust_->setYawThrust(0.5);
    else if (action == "get sensors")
        sendSensorReport(connfd);
    else if (action == "close connection")
        return false;

    return true;
}



void RCServer::sendSensorReport(int connfd)
{
    Json::Value obj;
    obj["ret"] = "hi";

    Json::FastWriter writer;
    send(connfd, writer.write(obj));
}



void RCServer::send(int connfd, const std::string& data)
{
    memcpy(ioBuffer_, data.c_str(), data.size() + 1);
    write(connfd, ioBuffer_, data.size() + 1);
}
