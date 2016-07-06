#define DEBUG
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

class Capture {
public:
    Capture();
    void startThreads(std::istream& in, std::ostream& out);
protected:
    virtual void process(cv::Mat& img) = 0;
    virtual void handleInput(std::string command, std::ostream& out);
    void startInput(std::istream& in, std::ostream& out);
    void startRecord();
    cv::Mat grayScale(cv::Mat img);
    int convertXCoordinate(int x);
    int convertYCoordinate(int y);

    bool keepRunning = true;
    int frameWidth;
    int frameHeight;
    std::vector<std::thread> _captureThreads;
    cv::Mat frame;
    cv::VideoCapture _capture;
};
