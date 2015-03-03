
#ifndef RC_SERVER
#define RC_SERVER

#include "../kernel/API/PowerManagement.h"
#include "../kernel/API/ThrustController.h"
#include "../kernel/API/IMUSensor.h"

#include <cstring>
#include <string>

class RCServer
{
    public:
        const std::size_t IO_BUFF_LEN = 1024;

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
