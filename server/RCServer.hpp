
#ifndef RC_SERVER
#define RC_SERVER

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
        void send(int, const std::string&);

    private:
        int listenfd_;
        char* ioBuffer_;
};

#endif
