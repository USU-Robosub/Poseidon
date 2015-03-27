
#include <RCServer.hpp>
#include "../kernel/API/PowerManagement.h"
#include "../kernel/API/ThrustController.h"
#include "../kernel/API/IMUSensor.h"

#include <libs/jsoncpp-1.5.0/json/json.h>
#include <netdb.h>
#include <unistd.h>
#include <pstream.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>


RCServer::RCServer(int port)
{
    power_ = std::make_shared<PowerManagement>();
    thrust_ = std::make_shared<ThrustController>();
    ioBuffer_ = new char[IO_BUFF_LEN];

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

        std::thread handler([connfd, this](){
            std::cout << "RC Server: accepted" << std::endl;
            std::cout.flush();

            bool keepAlive = true;

            do
            {
                auto len = read(connfd, ioBuffer_, IO_BUFF_LEN); // read data from client
                keepAlive = process(connfd, std::string(ioBuffer_, len));

            } while (keepAlive);

            close(connfd); // close connection
            sleep(50);
        });

        handler.detach();
    }
}



bool RCServer::process(int connfd, const std::string& input)
{
    if (input.length() == 0)
        return false;

    std::cout << "RC Server: received " << input << std::endl;

    Json::Value received;
    Json::Reader reader;

    if (!reader.parse(input, received))
        return false;

    auto effect = received["effect"].asString();
    auto action = received["action"].asString();

    std::string answer;

    if (effect == "power")
    {
        if (action == "enable")
        {
            answer = "Enabling ESCs...";
            power_->turnOnESCs();
        }
        else if (action == "disable")
        {
            answer = "Disabling ESCs...";
            power_->turnOffESCs();
        }
    }
    else if (effect == "thrust")
    {
        float newVal = received.get("value", "UTF-8").asFloat();

        if (action == "set forward")
        {
            answer = "Forward thrust to " + std::to_string(newVal);
            thrust_->setForwardThrust(newVal);
        }
        else if (action == "set pan")
        {
            answer = "Pan thrust to " + std::to_string(newVal);
            thrust_->setPanThrust(newVal);
        }
        else if (action == "set dive")
        {
            answer = "Dive thrust to " + std::to_string(newVal);
            thrust_->setDiveThrust(newVal);
        }
        else if (action == "set yaw")
        {
            answer = "Yaw thrust to " + std::to_string(newVal);
            thrust_->setYawThrust(newVal);
        }

        //trim trailing zeros
        answer.erase (answer.find_last_not_of('0') + 1, std::string::npos);
    }
    else if (effect == "network")
    {
        if (action == "code")
        {
            //receive the sent code
            std::string code = received.get("value", "UTF-8").asString();

            //read prefix file, save contents to rStream
            std::ifstream prefixFile("RubyPrefix.rb");
            std::stringstream rStream;
            std::string line;
            if (prefixFile.is_open())
            {
                while (getline(prefixFile, line))
                    rStream << line << std::endl;
                prefixFile.close();
            }

            //write to the Ruby file
            std::ofstream rubyFile;
            rubyFile.open("RubyRC.rb");
            rubyFile << rStream.str() << std::endl << code;
            rubyFile.close();

            //execute the Ruby
            //adapted from http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
            redi::ipstream proc("ruby RubyRC.rb > RubyOut.txt 2>&1", redi::pstreams::pstderr);

            // read child's stdout
            //while (std::getline(proc.out(), line))
            //std::cout << "stdout: " << line << 'n';
            // read child's stderr
            //while (std::getline(proc.err(), line))
            //std::cout << "stderr: " << line << 'n';

            answer = "Ruby code running!";
        }
    }
    else if (effect == "get")
    {
        if (action == "sensors")
        {
            //answer = "Sensor report requested.";
            sendSensorReport(connfd);
        }
        else if (action == "log")
        {
            //todo
        }
    }
    else if (effect == "network")
    {
        if (action == "ping")
        {
            answer = "pong";
        }
        else if (action == "close")
        {
            std::cout << "Closing network connection." << std::endl;
            return false;
        }
    }

    if (!answer.empty())
    {
        //send reply back to client
        Json::Value obj;
        obj["return"] = answer;
        Json::FastWriter writer;
        send(connfd, writer.write(obj));
    }

    std::cout << "Action complete" << std::endl;

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
    memcpy(ioBuffer_, data.c_str(), data.size());
    write(connfd, ioBuffer_, data.size());
}
