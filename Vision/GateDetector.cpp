#include "GateDetector.h"

// consider passing in parameters for color
GateDetector::GateDetector() : Capture()
{
    _lowHue = 91;
    _highHue = 179;
    _lowSaturation = 61;
    _highSaturation = 145;
    _lowValue = 116;
    _highValue = 255;

    for(int i = 0; i < QUEUE_SIZE; i++){
        _leftXs.push_back(0);
        _rightXs.push_back(0);
        _leftYs.push_back(0);
        _rightYs.push_back(0);
    }
}

void GateDetector::process(cv::Mat img)
{
    cv::Mat grayImg = Capture::grayscale(img);
    cv::Mat thresholdedImg;

    cv::inRange(grayImg, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), thresholdedImg);

    cv::Mat edgesImg, cdst;
    std::vector<cv::Vec4i> lines;

    cv::Canny(thresholdedImg, edgesImg, 50, 200, 3); // detects edges (not necessarily lines)

    cv::cvtColor(edgesImg, cdst, CV_GRAY2BGR);

    cv::HoughLinesP(edgesImg, lines, 1, CV_PI/180, 1, 100, 100);
    if(lines.size() > 0)
    {
        std::cout << lines.size() << std::endl;
        for( size_t i = 0; i < lines.size(); i++ )
        {
            cv::Vec4i l = lines[i];
            cv::line( cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
        }
    }

    cv::imwrite("thresh.jpg", thresholdedImg);
    cv::imwrite("lines.jpg", cdst);
    //cv::imshow("lines", cdst);
    //cv::waitKey(30);
}

void GateDetector::handleInput(int command)
{
    Capture::handleInput(command);
    
}
