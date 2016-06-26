#include "Capture.h"

Capture::Capture() { }

void Capture::startRecord()
{
    _capture.open(0);
    frameWidth = (int)_capture.get(CV_CAP_PROP_FRAME_WIDTH);
    frameHeight = (int)_capture.get(CV_CAP_PROP_FRAME_HEIGHT);

    while (keepRunning) {
        _capture >> frame;
        // Add in something to make sure the camera recorded
        process(frame); // Run image processing on the frame
#ifdef DEBUG
        cv::imshow("flow", frame); // Used for testing, but will be removed when running on Pi
        cv::waitKey(30); // Also a UI component, can be removed
#endif
    }
}

void Capture::startThreads()
{
    _captureThreads.push_back(std::thread(&Capture::startInput, this));
    _captureThreads.push_back(std::thread(&Capture::startRecord, this));

    for(auto i = 0u; i < _captureThreads.size(); i++)
    {
        _captureThreads[i].join();
    }
}

// We decided to put the origin at the middle of the camera to make it easier for the brain
// This converts an absolute x-coordinate to a relative one based on the camera resolution
int Capture::convertXCoordinate(int x)
{
    return x - frameWidth / 2;
}

int Capture::convertYCoordinate(int y)
{
    return (y - frameHeight / 2) * -1;
}

cv::Mat Capture::grayScale(cv::Mat img)
{
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2HSV);

    return grayImg;
}

void Capture::handleInput(std::string command)
{
    if(command.compare("quit") == 0)
    {
        keepRunning = false;
    }
}

// All of this code can be run from the main execution program as well, a pointer to the object would just need to be passed in
void Capture::startInput()
{
    // int exit = false;
    std::string command;
    while(keepRunning){
        std::cin >> command; // will be replaced with socket commands

        handleInput(command);
    }
}
