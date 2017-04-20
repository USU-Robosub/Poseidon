#include "ActionThread.h"

ActionThread::ActionThread(Serial& serial, std::ostream& out)
    : serial_(serial), out_(out), liveStatus(false) {
}

void* actionThread_callback(void*data) {
    ActionThread thread = *((ActionThread*)data);
    for(;;) {
        // read indefinitely
        thread._read();
    }
    return NULL;
}

void ActionThread::begin() {
    std::cerr << "Begining Action Thread\n";
    
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
    
    int res = pthread_create(&thread_, &attributes, actionThread_callback, (void*)this);
    
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

void ActionThread::_read() {
    unsigned char res = serial_.readByte();
    std::cout << "Event value: " << (int)res << std::endl;
    auto outJson = json{
            {"Type", "ActionEvent"},
            {"Value", res}
    };
    
#ifdef DEBUG
    std::cerr << outJson << std::endl;
#endif

    out_ << outJson << std::endl;
}