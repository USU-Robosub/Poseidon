#include <pthread.h>
#include <chrono>

#include <sstream>
#include <unistd.h>
#include <fcntl.h>

#include <json.h>
using json = nlohmann::json;

#include "ActionThread.h"

ActionThread::ActionThread(unsigned int gpio, std::ostream& out)
    : out_(out), endOfThread(true) {
    std::stringstream ss1, ss2;
    ss1 << "/sys/class/gpio/gpio" << gpio << "/edge";
    ss2 << "/sys/class/gpio/gpio" << gpio << "/value";
    edgefd_ = ss1.str();
    valuefd_ = ss2.str();
    std::cerr << valuefd_ << "\n";
}

void* actionThread_callback(void*data) {
    ActionThread thread = *((ActionThread*)data);
    while(true) {
        thread._read();
    }
    return NULL;
}

void ActionThread::begin() {
    std::cerr << "Begining Action Thread\n";
    
    gpio_[0].fd = open(valuefd_.c_str(), O_RDONLY);
    gpio_[0].events = POLLPRI;
    
    if(gpio_[0].fd <= 0) {
        std::cerr << "Failed to open gpio file\n";
        return;
    }
    
    endOfThread = false;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
    int res = pthread_create(&thread_, &attributes, actionThread_callback, (void*)this);
    if(res) {
        endOfThread = true;
        std::cerr << "Failed to create event thread\n";
    }
}

void ActionThread::end() {
    std::cerr << "Ending Action Thread\n";
    endOfThread = true;
    void* exitStatus;
    pthread_cancel(thread_);
    pthread_join(thread_, &exitStatus);
    close(gpio_[0].fd);
}

bool ActionThread::isLive() {
    return !endOfThread;
}

void ActionThread::setEdge(EdgeMode mode) {
    int fd = open(edgefd_.c_str(), O_WRONLY);
    std::stringstream ss;
    switch(mode) {
        case NONE:    ss<<"none";    break;
        case RISING:  ss<<"rising";  break;
        case FALLING: ss<<"falling"; break;
        case BOTH:    ss<<"both";    break;
    }
    std::string ret = ss.str();
    write(fd, ret.c_str(), ret.size());
    close(fd);
}

void ActionThread::_read() {
    char res[1];
    
    poll(gpio_, 1, -1);
    if (gpio_[0].revents & POLLPRI) {
		lseek(gpio_[0].fd, 0, SEEK_SET);
		read(gpio_[0].fd, res, 1);
		std::cerr << "Interrupt: " << res[0] << "\n";
		sendJS(res[0]);
	}
}

void ActionThread::sendJS(char value) {
    auto outJson = json{
            {"Type", "ActionEvent"},
            {"Value", value}
    };
    #ifdef DEBUG
        std::cerr << outJson << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    #endif
    out_ << outJson << std::endl;
}