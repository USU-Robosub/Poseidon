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
    void refreshHsv();
    void setHsvValues(json hsvJson);

private:
    cv::Mat thresholdImage_(cv::Mat& image);
    json rectanglesToPoles_(std::vector<cv::RotatedRect>& rectangles);
    json rectangleToPole_(cv::RotatedRect& rectangle);
    int _lowHue = 0;
    int _highHue = 255;
    int _lowSaturation = 0;
    int _highSaturation = 255;
    int _lowValue = 0;
    int _highValue = 255;

    json poles_ = json::array();
};
