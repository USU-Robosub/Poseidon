
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
        RCServer(int port);
        ~RCServer();
        void start();
        bool process(int, const std::string&);
        void sendSensorReport(int);
        void send(int, const std::string&);

    private:
        std::shared_ptr<PowerManagement> power_;
        std::shared_ptr<ThrustController> thrust_;
        std::shared_ptr<IMUSensor> imu_;

        int listenfd_;
        char* ioBuffer_;
};

#endif

