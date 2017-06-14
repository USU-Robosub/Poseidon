#ifndef ACTION_THREAD_H
#define ACTION_THREAD_H

#include <pthread.h>
#include <ostream>
#include <json.h>
#include "Serial.h"

using json = nlohmann::json;

class ActionThread {
private:
    typedef struct Object {
        void* data1;
        void* data2;
    } Object;

    Serial& serial_;
    pthread_t thread_;
    std::ostream& out_;
    
    bool isLive_;

public:
    ActionThread(Serial& serial, std::ostream& out);
    
    void begin();
    void end();
    bool isLive();
    
    void _read();
};

#endif