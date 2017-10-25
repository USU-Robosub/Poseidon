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
    ~GateDetector();

private:
    const int TEMPLATE_COUNT = 1;
    const int SCALE_FACTOR_X = 1280;
    const int SCALE_FACTOR_Y = 720;

	void scaleTemplates(cv::Mat camera);
    cv::RotatedRect thresholdImage_(cv::Mat& image, cv::Mat& imageTemplate);
    json rectangleToPole_(cv::RotatedRect& rectangle);
    cv::Mat *template_;

    json poles_ = json::array();


};
