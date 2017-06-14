#ifndef ACTION_THREAD_H
#define ACTION_THREAD_H

#include <ostream>
#include <string>
#include <poll.h>

class ActionThread {
private:
    typedef struct Object {
        void* data1;
        void* data2;
    } Object;

    struct pollfd gpio_[1];

    std::string edgeFd_;
    std::string valueFd_;
    pthread_t thread_;
    std::ostream& out_;

    volatile bool isLive_;

    void sendJS(char value);

public:
    enum EdgeMode {
        NONE,
        RISING,
        FALLING,
        BOTH
    };

    ActionThread(unsigned int gpio, std::ostream& out);

    void begin();
    void end();
    bool isLive();
    void setEdge(EdgeMode mode);
    
    void _read();
};

#endif