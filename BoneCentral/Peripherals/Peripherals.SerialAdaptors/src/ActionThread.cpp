#include "ActionThread.h"

ActionThread::ActionThread(Serial& serial, std::ostream& out)
    : serial_(serial), out_(out), isLive_(false) {
}

void* actionThread_callback(void* data) {
    ActionThread thread = *((ActionThread*)data);
    while(true) {
        // read indefinitely
        thread._read();
    }
    return NULL;
}

void ActionThread::begin() {
    std::cerr << "Beginning Action Thread\n";
    
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
    
    auto res = pthread_create(&thread_, &attributes, actionThread_callback, (void*)this);

    isLive_ = true;
    if(res) {
        isLive_ = false;
        std::cerr << "Failed to create event thread\n";
    }
}

void ActionThread::end() {
    std::cerr << "Ending Action Thread\n";
    
    void* exitStatus;
    pthread_cancel(thread_);
    pthread_join(thread_, &exitStatus);
    isLive_ = false;
}

bool ActionThread::isLive() {
    return isLive_;
}

void ActionThread::_read() {
    unsigned char response = serial_.readByte();
    std::cout << "Event value: " << (int)response << std::endl;
    auto outJson = json{
            {"Type", "ActionEvent"},
            {"Value", response}
    };
    
#ifdef DEBUG
    std::cerr << outJson << std::endl;
#endif

    out_ << outJson << std::endl;
}