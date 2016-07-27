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
    cv::RotatedRect thresholdImage_(cv::Mat& image);
    json rectangleToPole_(cv::RotatedRect& rectangle);
    cv::Mat template_;

    json poles_ = json::array();
};
