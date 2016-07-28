#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
const int TEMP_COUNT = 2;
Mat tmpary[TEMP_COUNT];
Mat result;
VideoCapture stream;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	/// Load image and template
	tmpary[0] = imread("C:\\Users\\na\\Documents\\Visual Studio 2013\\Projects\\OCV_Template\\x64\\Debug\\gate_template_2.png", 1);
	tmpary[1] = imread("C:\\Users\\na\\Documents\\Visual Studio 2013\\Projects\\OCV_Template\\x64\\Debug\\gate_template.png", 1);

	// make sure all templates are loaded correctly
	for (int i = 0; i < TEMP_COUNT; i++){
		if (!tmpary[i].data)
			return 1;
	}

	stream.open("C:\\Users\\na\\Documents\\Visual Studio 2013\\Projects\\OCV_Template\\x64\\Debug\\gate_onsite.mp4");

	/// Create windows
	namedWindow(image_window, CV_WINDOW_AUTOSIZE);

	/// Create Trackbar
	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
	
	while ((char)waitKey(1) != (char)27) {
		MatchingMethod(0, 0);
	}

	return 0;
}

/**
* @function MatchingMethod
* @brief Trackbar callback
*/
void MatchingMethod(int, void*)
{
	/// Source image to display
	Mat img_display;
	stream.read(img_display);

	int idx = 0;

	/// Create the result matrix
	int result_cols = img_display.cols - tmpary[idx].cols + 1;
	int result_rows = img_display.rows - tmpary[idx].rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(img_display, tmpary[idx], result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	/// Localizing the best match with minMaxLoc
	double minVal;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	/// Show me what you got
	rectangle(img_display, matchLoc, Point(matchLoc.x + tmpary[idx].cols, matchLoc.y + tmpary[idx].rows), Scalar::all(0), 2, 8, 0);
	//rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, img_display);
	imshow(result_window, result);

	return;
}