#include <iostream>
#include <list>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

 int main( int argc, char** argv )
 {
    cv::VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         std::cout << "Cannot open the web cam" << std::endl;
         return -1;
    }

    // THESE ARE SET FOR THE ORANGE COLOR
    int iLowH = 0;
    int iHighH = 27;

    int iLowS = 194; 
    int iHighS = 255;

    int iLowV = 92;
    int iHighV = 214;
    
    cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    //Create trackbars in "Control" window
    cv::createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cv::createTrackbar("HighH", "Control", &iHighH, 179);

    cv::createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cv::createTrackbar("HighS", "Control", &iHighS, 255);

    cv::createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    cv::createTrackbar("HighV", "Control", &iHighV, 255);
    

    std::list<float> leftXs;
    std::list<float> rightXs;
    std::list<float> leftYs;
    std::list<float> rightYs;
    int QUEUE_SIZE = 20;
    for(int i = 0; i < QUEUE_SIZE; i++){
        leftXs.push_back(0);
        rightXs.push_back(0);
        leftYs.push_back(0);
        rightYs.push_back(0);
    }

    int iLastX = -1; 
    int iLastY = -1;

    //Capture a temporary image from the camera
    cv::Mat imgTmp;
    cap.read(imgTmp); 

    //Create a black image with the size as the camera output
    cv::Mat imgLines = cv::Mat::zeros( imgTmp.size(), CV_8UC3 );;

    while (true)
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

        cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
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
        double avgX = 0, avgY = 0;

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

        cv::line( cdst, cv::Point(rightX, avgY - 50), cv::Point(rightX, avgY + 50), cv::Scalar(0,0,255), 3, CV_AA);
        cv::line( cdst, cv::Point(leftX, avgY - 50), cv::Point(leftX, avgY + 50), cv::Scalar(0,0,255), 3, CV_AA);
        cv::line( cdst, cv::Point(avgX, avgY - 50), cv::Point(avgX, avgY + 50), cv::Scalar(0,0,255), 3, CV_AA);

        cv::imshow("detected lines", cdst);
        /////////////////////////////

        cv::imshow("Thresholded Image", imgThresholded); //show the thresholded image

        imgOriginal = imgOriginal + imgLines;
        cv::imshow("Original", imgOriginal); //show the original image

        if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break; 
        }
    }

   return 0;
}
