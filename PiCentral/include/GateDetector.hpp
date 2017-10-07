#ifndef PICENTRAL_GATE_DETECTOR_HPP
#define PICENTRAL_GATE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

#include "Capture.hpp"

class GateDetector : public Capture {
protected:
	void process(cv::Mat& img);
};

#endif