#include "GateDetector.h"

// consider passing in parameters for color
GateDetector::GateDetector() : Capture()
{
    _lowHue = 0;
    _highHue = 19;
    _lowSaturation = 204;
    _highSaturation = 255;
    _lowValue = 0;
    _highValue = 155;

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

    // Only considers pixels in the correct color range
    cv::inRange(grayImg, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), thresholdedImg);

    // Morphological opening (removes small objects from the foreground)
    cv::erode(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 

    // Morphological closing (removes small holes from the foreground)
    cv::dilate(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 
    cv::erode(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    
    cv::Mat edgesImg, cdst;
    std::vector<cv::Vec4i> lines;

    // Detect edges
    cv::Canny(thresholdedImg, edgesImg, 50, 200, 3);

    cv::cvtColor(edgesImg, cdst, CV_GRAY2BGR);

    cv::HoughLinesP(edgesImg, lines, 1, CV_PI/180, 50, 100, 10);
    if(lines.size() > 0)
    {
        //std::cout << lines.size() << std::endl;
        for( size_t i = 0; i < lines.size(); i++ )
        {
            cv::Vec4i line = lines[i];
            if(std::abs(line[0] - line[2]) <= 25)
            {
                std::cout << "WIDTH: " << frameWidth << " HEIGHT: " << frameHeight << std::endl;
                std::cout << "x1: " << convertXCoordinate(line[0]) << " y1: " << convertYCoordinate(line[1]) << std::endl;
                std::cout << "x2: " << convertXCoordinate(line[2]) << " y2: " << convertYCoordinate(line[3]) << std::endl;
                cv::line( cdst, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0,0,255), 3, CV_AA);
            }
        }
    }

    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", cdst);
    cv::imshow("lines", cdst);
    cv::waitKey(30);
}

void GateDetector::handleInput(int command)
{
    Capture::handleInput(command);
    
}
