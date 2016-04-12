#include "Capture.h"

Capture * Capture::_instance = NULL;

// private constructor (Singleton pattern)
Capture::Capture() { }

Capture* Capture::instance() 
{
    if (_instance == NULL)
    {
        _instance = new Capture();
    }
    return _instance;
}

void Capture::StartRecord(Capture * cap)
{
    cap->record();
}

void Capture::record()
{
    _cap.open(0);

    while (keepRunning) {
        _cap >> frame;
        // run img processing on the frame
        cv::imshow("flow", frame);
        cv::waitKey(30);
    }
}

void Capture::StartInput(Capture * cap)
{
    cap->inputLoop();
}

// All of this code can be run from the main execution program as well, a pointer to the object just needs to be passed in
void Capture::inputLoop()
{
    int exit = false;
    int command;
    while(exit == false){
        std::cin >> command; // will be replaced with socket commands
        switch(command)
        {
            case 1:
                //std::cout << gatesDetected() << std::endl;
                break;
            case 2:
                //std::cout << gateXPosition() << std::endl;
                break;
            case -1:
                exit = true;
                keepRunning = false;
                break;
            default:
                break;

        }
    }

    std::cout << "Exiting" << std::endl;
}
