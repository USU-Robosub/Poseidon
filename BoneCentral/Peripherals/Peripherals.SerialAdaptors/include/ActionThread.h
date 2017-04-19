#ifndef ACTION_THREAD_H
#define ACTION_THREAD_H

#include <pthread.h>
#include "Serial.h"

class ActionThread {
private:
    Serial& serial_;
    pthread_t thread_;
    bool liveStatus;

public:
    ActionThread(Serial& serial);
    
    void begin();
    void end();
    bool isLive();
};

#endif