#include "Capture.h"
#include <utility>
#include <tuple>

struct Pole {

};

class GateDetector : public Capture
{
public:
    void process(cv::Mat img);
    void handleInput(std::string command);

private:
    void clusterPoles(std::vector<int> lineXCoords);
    int averageLines(std::vector<int> lineXCoords);
    std::vector<int> lineXCoords;
    const int ANGLE = 25;
    const int MAX_DIST = 50;
    float averageXCoord = 0;
    // Used for finding the orange color, subject to change
    int _lowHue = 0;
    int _highHue = 179;
    int _lowSaturation = 0;
    int _highSaturation = 133;
    int _lowValue = 0;
    int _highValue = 255;

    int rightGateX = -1;
    int leftGateX = -1;
};
