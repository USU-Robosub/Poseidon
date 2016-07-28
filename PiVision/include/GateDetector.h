#include "Capture.h"
#include <utility>
#include <tuple>
#include <json.h>
#include <fstream>

using json = nlohmann::json;

class GateDetector : public Capture
{
public:
    GateDetector();
    void process(cv::Mat& img);
    void handleInput(std::string command, std::ostream& out);

private:
	void scaleTemplates();
    cv::RotatedRect thresholdImage_(cv::Mat& image);
    json rectangleToPole_(cv::RotatedRect& rectangle);
    cv::Mat template_[TEMPLATE_COUNT];

    json poles_ = json::array();

    const int TEMPLATE_COUNT = 2;
	const int SCALE_FACTOR_X = 1280;
	const int SCALE_FACTOR_Y = 720;
};
