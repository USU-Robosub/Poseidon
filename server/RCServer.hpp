/**
  * \class RCServer
  *
  *  Created on: Mar 20, 2015
  *      Author: Jesse Victors
  *
  * \brief This is object designed to provide a remote interface for manual control and analysis.
  */

#ifndef RC_SERVER
#define RC_SERVER

#include "../kernel/API/PowerManagement.h"
#include "../kernel/API/ThrustController.h"
#include "../kernel/API/IMUSensor.h"

#include <cstring>
#include <string>

#define IO_BUFF_LEN 1024

class RCServer
{
    public:
        /** \brief Initializes a new instance of a server interface.
          */
        RCServer();
        ~RCServer();

        void setPort(int port);

        /** \brief Starts up the server and begins listening for requests.
          */
        void start();

        /** \brief Processes a provided string by parsing and executing valid commands.
          * \param connfd A connection file descriptor.
          * \param input The string representation of commands to be processed.
          */
        bool process(int, const std::string&);

        /** \brief Sends a collection of sensor information to the client.
          * \param connfd A connection file descriptor to send through.
          */
        void sendSensorReport(int);

        /** \brief Sends a string of information to the client.
          * \param connfd A connection file descriptor to send through.
          * \param data A string containing information to send.
          */
        void send(int, const std::string&);

    private:
        std::shared_ptr<PowerManagement> power_;
        std::shared_ptr<ThrustController> thrust_;
        std::shared_ptr<IMUSensor> imu_;

        int listenfd_;
        char* ioBuffer_;
};

#endif

