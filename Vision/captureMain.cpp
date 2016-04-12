#include "Capture.h"

int main(int argc, char** argv) {
    Capture::instance()->capThreads.push_back(std::thread(&Capture::StartInput, Capture::instance()));
    Capture::instance()->capThreads.push_back(std::thread(&Capture::StartRecord, Capture::instance()));

    for (int i = 0; i < Capture::instance()->capThreads.size(); i++) {
        Capture::instance()->capThreads[i].join();
    }
}
