#include "GateDetector.h"

int GateDetector::averageLines(std::vector<int> lineXCoords)
{
    float totalX = 0;
    for( size_t i = 0; i < lineXCoords.size(); i++ )    
    {
        totalX += lineXCoords[i];
    }

    return int(totalX / lineXCoords.size());
}

void GateDetector::clusterPoles(std::vector<int> lineXCoords)
{
    bool left = true;
    std::vector<int> xPos;
    std::sort(lineXCoords.begin(), lineXCoords.end());

    if(lineXCoords.size() > 1)
    {
        xPos.push_back(lineXCoords[0]);
        for(size_t i = 1; i < lineXCoords.size(); i++)
        {
            if(lineXCoords[i] - xPos[i - 1] > MAX_DIST || i == lineXCoords.size() - 1)
            {
                if(left)
                {
                    leftGateX = averageLines(xPos);
                    left = false;
                    xPos.clear();
                }
                else
                {
                    rightGateX = averageLines(xPos);
                }
            }

            xPos.push_back(lineXCoords[i]);
        }
    }
    else
    {
        leftGateX = -1;
        rightGateX = -1;
    }

    averageXCoord = averageLines(lineXCoords);
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

    // Simplify the color
    cv::cvtColor(edgesImg, cdst, CV_GRAY2BGR);

    // Find all lines of a certain length
    cv::HoughLinesP(edgesImg, lines, 1, CV_PI/180, 50, 100, 10);
    if(lines.size() > 0)
    {
        lineXCoords.clear();
        // Iterate through lines
        for( size_t i = 0; i < lines.size(); i++ )
        {
            cv::Vec4i line = lines[i];
            // Make sure the line isn't horizontal
            if(std::abs(line[0] - line[2]) <= ANGLE)
            {
                lineXCoords.push_back(convertXCoordinate(line[0]));
                lineXCoords.push_back(convertXCoordinate(line[2]));
                /*
                // Debugging to give position and draw lines on the detected gates
                std::cout << "WIDTH: " << frameWidth << " HEIGHT: " << frameHeight << std::endl;
                std::cout << "x1: " << convertXCoordinate(line[0]) << " y1: " << convertYCoordinate(line[1]) << std::endl;
                std::cout << "x2: " << convertXCoordinate(line[2]) << " y2: " << convertYCoordinate(line[3]) << std::endl;
                cv::line( cdst, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0,0,255), 3, CV_AA);
                */
            }
        }

        clusterPoles(lineXCoords);
    }

    // If you want to save images
    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", cdst);

    // If you want to show the image on screen (debugging only)
    //cv::imshow("lines", cdst);

    // Must stay in if you are debugging
    cv::waitKey(30);
}

void GateDetector::handleInput(std::string command)
{
    Capture::handleInput(command);

    if(command.compare("GATE_center") == 0)
    {
        std::cout << averageXCoord << std::endl;
    }
    else if(command.compare("GATE_right") == 0)
    {
        std::cout << rightGateX << std::endl; // give you the avg right gate position
    }
    else if(command.compare("GATE_left") == 0)
    {
        std::cout << leftGateX << std::endl; // give the avg left gate position
    }
    else if(command.compare("GATE_allX") == 0)
    {
        // here you could send the line x coordinates through the socket
        std::cout << lineXCoords.size() << std::endl;
    }
}
