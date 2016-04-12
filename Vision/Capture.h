#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <vector>
#include <chrono>

class Capture {
public:
    void record();
    void inputLoop();
    static void StartInput(Capture * cap);
    static void StartRecord(Capture * cap);

    bool keepRunning = true;
    std::vector<std::thread> capThreads;
private:
    cv::Mat frame;
    cv::VideoCapture _cap;
    Capture();
    static Capture * _instance;
public:
    static Capture *instance();
};
