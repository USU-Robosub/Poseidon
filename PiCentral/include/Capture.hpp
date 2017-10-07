#ifndef PI_CENTRAL_CAPTURE_HPP
#define PI_CENTRAL_CAPTURE_HPP

#include <string>
#include <opencv2/opencv.hpp>

class Capture {
public:
	Capture();
	
	void start(unsigned int camera);
	void start(std::string source_url);
	
protected:
	virtual void process(cv::Mat& img) = 0;

	cv::VideoCapture _capture;
	cv::Mat _frame;
	bool _should_run;
	
private:
	void run();
};

#endif