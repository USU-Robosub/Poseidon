
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
    thrust_(std::make_shared<ThrustController>())
    //imu_(std::make_shared<IMUSensor>())
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

    Json::Value received;
    Json::Reader reader;

    bool parsedSuccess = reader.parse(input, received);

   // std::cout << parsedSuccess << std::endl;
    auto effect = received["effect"].asString();
    auto action = received["action"].asString();
    //std::cout << effect << " | " << action << std::endl;
    //std::cout.flush();

    if (effect == "power")
    {
        if (action == "enable power")
            std::cout << "enabling ESCs..." << std::endl;//power_->turnOnESCs();
        else if (action == "disable power")
            std::cout << "disabling ESCs..." << std::endl; //power_->turnOffESCs();
    }
    else if (effect == "thrust")
    {
        float newVal = received.get("value", "UTF-8").asFloat();

        if (action == "set forward")
            std::cout << "Forward thrust to " << newVal << std::endl; //thrust_->setForwardThrust(0.5);
        else if (action == "set drift")
            std::cout << "Drift thrust to " << newVal << std::endl; //thrust_->setDriftThrust(0.5);
        else if (action == "set dive")
            std::cout << "Dive thrust to " << newVal << std::endl; //thrust_->setDiveThrust(0.5);
        else if (action == "set yaw")
            std::cout << "Yaw thrust to " << newVal << std::endl; //thrust_->setYawThrust(0.5);
    }
    else if (effect == "get")
    {
        if (action == "sensors")
            sendSensorReport(connfd);
    }
    else if (effect == "network")
    {
        if (action == "close")
            return false;
    }

    return true;
}



void RCServer::sendSensorReport(int connfd)
{
    Json::Value obj;
    obj["return"] = "sensors";
    obj["sampleSensor"] = 42;

    Json::FastWriter writer;
    send(connfd, writer.write(obj));
}



void RCServer::send(int connfd, const std::string& data)
{
    memcpy(ioBuffer_, data.c_str(), data.size() + 1);
    write(connfd, ioBuffer_, data.size() + 1);
}
