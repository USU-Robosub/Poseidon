
#ifndef RC_SERVER
#define RC_SERVER

#include <cstring>

class RCServer
{
    public:
        const std::size_t IO_BUFF_LEN = 1024;

        RCServer(int port);
        void start();

    private:
        int listenfd_;
};

#endif
