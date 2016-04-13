#include "Capture.h"

Capture::Capture() { }

void Capture::startRecord()
{
    _capture.open(0);

    while (keepRunning) {
        _capture >> frame;
        // Add in something to make sure the camera recorded
        process(frame); // Run image processing on the frame
        //cv::imshow("flow", frame); // Used for testing, but will be removed when running on Pi
        //cv::waitKey(30); // Also a UI component, can be removed
    }
}

void Capture::startThreads()
{
    _captureThreads.push_back(std::thread(&Capture::startInput, this));
    _captureThreads.push_back(std::thread(&Capture::startRecord, this));

    for(int i = 0; i < _captureThreads.size(); i++)
    {
        _captureThreads[i].join();
    }
}

void Capture::process(cv::Mat img)
{
    std::cout << "In parent" << std::endl;
}

cv::Mat Capture::grayscale(cv::Mat img)
{
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2HSV);

    return grayImg;
}

void Capture::handleInput(int command)
{
    if(command == -1)
    {
        keepRunning = false;
    }
}

// All of this code can be run from the main execution program as well, a pointer to the object just needs to be passed in
void Capture::startInput()
{
    int exit = false;
    int command;
    while(keepRunning){
        std::cin >> command; // will be replaced with socket commands

        // Using int codes for now, will be more advanced in the future
        handleInput(command);
    }
}
