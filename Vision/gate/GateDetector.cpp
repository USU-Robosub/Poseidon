#include "GateDetector.h"

GateDetector::GateDetector()
{
    continueCapture = false;
    rightGatePosition = 0;
    leftGatePosition = 0;
    centerPosition = 0;
    for(int i = 0; i < QUEUE_SIZE; i++){
        leftXs.push_back(0);
        rightXs.push_back(0);
        leftYs.push_back(0);
        rightYs.push_back(0);
    }
    LOW_HUE = 0;
    HIGH_HUE = 27;
    LOW_SATURATION = 194;
    HIGH_SATURATION = 255;
    LOW_VALUE = 92;
    HIGH_VALUE = 214;

    QUEUE_SIZE = 20;
}

void GateDetector::stopCapture()
{
    continueCapture = false;
}

float GateDetector::getRightGatePosition()
{
    return rightGatePosition;
}

float GateDetector::getLeftGatePosition()
{
    return leftGatePosition;
}

float GateDetector::getCenterPosition()
{
    return centerPosition;
}

void GateDetector::startCapture() // might want to pass in camera id -> 0, 1, etc.
{
    continueCapture = true;
    cv::VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         std::cout << "Cannot open the web cam" << std::endl;
         return;
    }

    int iLastX = -1; 
    int iLastY = -1;

    //Capture a temporary image from the camera
    cv::Mat imgTmp;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    cv::Mat imgLines = cv::Mat::zeros( imgTmp.size(), CV_8UC3 );;

    while (continueCapture)
    {
        cv::Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        cv::Mat imgHSV;

        cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
 
        cv::Mat imgThresholded;

        cv::inRange(imgHSV, cv::Scalar(LOW_HUE, LOW_SATURATION, LOW_VALUE), cv::Scalar(HIGH_HUE, HIGH_SATURATION, HIGH_VALUE), imgThresholded); //Threshold the image
      
        //morphological opening (removes small objects from the foreground)
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
        cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 

        //morphological closing (removes small holes from the foreground)
        cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) ); 
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

        //Calculate the moments of the thresholded image
        cv::Moments oMoments = cv::moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;

        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
        if (dArea > 10000)
        {
            //calculate the position of the ball
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;        
        
            if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                cv::line(imgLines, cv::Point(posX, posY), cv::Point(iLastX, iLastY), cv::Scalar(0,0,255), 2);
            }

            iLastX = posX;
            iLastY = posY;
        }

        // HOUGH LINE DETECTION
        cv::Mat dst, cdst;
        cv::Canny(imgThresholded, dst, 50, 200, 3);
        cv::cvtColor(dst, cdst, CV_GRAY2BGR);

        int closeLeftX = 0, 
            lowLeftY = 0, 
            farLeftX = 0,
            highLeftY = 0,
            closeRightX = 0,
            lowRightY = 0,
            farRightX = 0,
            highRightY = 0,
            THRESHOLD = 200;
        float avgX = 0, avgY = 0;

        std::vector<cv::Vec4i> lines;
        // img, output vector, rho, theta, threshold=50, minLineLength=50, maxLineGap=10 (original specs)
        cv::HoughLinesP(dst, lines, 1, CV_PI/180, 1, 100, 100 );
        if(lines.size() > 0)
        {
            for( size_t i = 0; i < lines.size(); i++ )
            {
                cv::Vec4i l = lines[i];
                avgX += l[0] + l[2];
                avgY += l[1] + l[3];
            }
            avgX /= (lines.size() * 2);
            avgY /= (lines.size() * 2);
        }

        int right = 0, left = 0;
        for( size_t i = 0; i < lines.size(); i++ )
        {
            cv::Vec4i l = lines[i];            
            // left means low

            // on the left            
            if (l[0] < avgX || l[2] < avgX){
                leftXs.pop_front();
                leftXs.pop_front();
                leftYs.pop_front();
                leftYs.pop_front();
                leftXs.push_back(l[0]);
                leftXs.push_back(l[2]);
                leftYs.push_back(l[1]);
                leftYs.push_back(l[3]);
            }

            // on the right
            if (l[0] > avgX || l[2] > avgX){
                rightXs.pop_front();
                rightXs.pop_front();
                rightYs.pop_front();
                rightYs.pop_front();
                rightXs.push_back(l[0]);
                rightXs.push_back(l[2]);
                rightYs.push_back(l[1]);
                rightYs.push_back(l[3]);
            }
        }

        float rightX = 0, leftX = 0, rightY = 0, leftY = 0;
        
        for (std::list<float>::const_iterator iterator = rightXs.begin(), end = rightXs.end(); iterator != end; ++iterator) {
            rightX += *iterator;
        }
        for (std::list<float>::const_iterator iterator = leftXs.begin(), end = leftXs.end(); iterator != end; ++iterator) {
            leftX += *iterator;
        }
        for (std::list<float>::const_iterator iterator = rightYs.begin(), end = rightYs.end(); iterator != end; ++iterator) {
            rightY += *iterator;
        }
        for (std::list<float>::const_iterator iterator = leftYs.begin(), end = leftYs.end(); iterator != end; ++iterator) {
            leftY += *iterator;
        }
        rightX /= QUEUE_SIZE;
        leftX /= QUEUE_SIZE;
        rightY /= QUEUE_SIZE;
        leftY /= QUEUE_SIZE;
        
        avgX = (rightX + leftX) / 2;
        avgY = (rightY + leftY) / 2;

        std::cout << avgX << ':' << avgY << std::endl;

        rightGatePosition = rightX;
        leftGatePosition = leftX;
        centerPosition = avgX;
    }
}
