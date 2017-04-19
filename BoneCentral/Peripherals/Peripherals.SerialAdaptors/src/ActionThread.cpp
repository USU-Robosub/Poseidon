#include "ActionThread.h"

ActionThread::ActionThread(Serial& serial)
    : serial_(serial), liveStatus(false) {
}

void* actionThread_callback(void* data) {
    Serial serial = *((Serial*)data);
    for(;;) {
        // read indefinitely
        unsigned char res = serial.readByte();
        std::cout << "Event value: " << (int)res << std::endl;
    }
}

void ActionThread::begin() {
    std::cerr << "Begining Action Thread\n";
    
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
    int res = pthread_create(&thread_, &attributes, actionThread_callback, (void*)&serial_);
    liveStatus = true;
    if(res) {
        liveStatus = false;
        std::cerr << "Failed to create event thread\n";
    }
}

void ActionThread::end() {
    std::cerr << "Ending Action Thread\n";
    
    void* exitStatus;
    pthread_cancel(thread_);
    pthread_join(thread_, &exitStatus);
    liveStatus = false;
}

bool ActionThread::isLive() {
    return liveStatus;
}