#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <vector>
#include <chrono>

class Capture {
public:
    Capture();
    void startThreads();
protected:
    virtual void process(cv::Mat img);
    virtual void handleInput(int command);
    void startInput();
    void startRecord();
    cv::Mat grayscale(cv::Mat img);

    bool keepRunning = true;
    std::vector<std::thread> _captureThreads;
    cv::Mat frame;
    cv::VideoCapture _capture;
};
