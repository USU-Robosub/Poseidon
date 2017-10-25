#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is pic1.png\n" << endl;
}

int main(int argc, char** argv)
{
    const char* filename = argc >= 2 ? argv[1] : "board.jpg";

    cout << "reading " << filename << endl;
    
    Mat img = imread(filename, 0);
    Mat img2 = imread( filename, 1 );
    imwrite("./color.jpg", img2);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    Mat cimg;
    medianBlur(img, img, 3);
    
    cvtColor(img, cimg, COLOR_GRAY2BGR);

    // void cv::HoughCircles(cv::InputArray, cv::OutputArray, int, double, double, double, double, int, int)’

    vector<Vec3f> circles;
    HoughCircles(img, circles, CV_HOUGH_GRADIENT, 1, 30,
                 ((argc >= 5) ? atoi(argv[4]) : 100), ((argc >= 6) ? atoi(argv[5]) : 24), ((argc >= 3) ? atoi(argv[2]) : 1),  ((argc >= 4) ? atoi(argv[3]) : 30) // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                                // default without command line parameters is 1 to 30
                 );
                 
    cout << "found a circle " << circles.size() << " times" << endl;
    for( size_t i = 0; i < circles.size(); i++ )
    {
        int x = 0;
        int y = 0;

        
        Vec3i c = circles[i];
        Point pt = Point(c[0], c[1]);
        Vec3b pixel = img2.at<Vec3b>(pt.y, pt.x);
        int b = pixel[0];
        int g = pixel[1];
        int r = pixel[2];
       
    
        x = pt.x - 640;
        if (pt.y <=  360)
        {
            y = 360 - pt.y;
        }
        else
        {
            y = -(pt.y - 360);
        }
        if(r >= 100 && g < r/2 && b < r/2) //for red
//      if(r >= 100 && g >= 100 && b < r/2) //for yellow
//      if(r < g/2 && g >= 100 && b < g/2) //for green? not tested, need buoy color
        {
            circle( cimg, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, CV_AA);
            circle( cimg, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, CV_AA);
            cout << "x: " << x << "   y: " << y << endl
                 << "RGB: " << r << "," << g << "," << b << endl
                 << "Image location: " << pt.x << "  " << pt.y << endl;
        }
    }

    // imshow("detected circles", cimg);
    cout << "writing output" << endl;
    imwrite("./found.jpg", cimg);
    // waitKey();

    return 0;
}