#include "Capture.h"
#include <utility>
#include <tuple>
#include <json.h>
#include <fstream>
using json = nlohmann::json;

struct Pole {

};

class GateDetector : public Capture
{
public:
    GateDetector();
    void process(cv::Mat img);
    void handleInput(std::string command);
    void refreshHsv();
    void setHsvValues(json hsvJson);

private:
    void clusterPoles(std::vector<int> lineXCoords);
    int averageLines(std::vector<int> lineXCoords);
    std::vector<int> lineXCoords;
    const int ANGLE = 25;
    const int MAX_DIST = 50;
    float averageXCoord = 0;

    // Used for finding the orange color, subject to change
    void readHsvValues_(json hsvJson);
    int _lowHue = 0;
    int _highHue = 255;
    int _lowSaturation = 0;
    int _highSaturation = 255;
    int _lowValue = 0;
    int _highValue = 255;

    int rightGateX = -1;
    int leftGateX = -1;
};
