#include "Capture.h"

class GateDetector : public Capture
{
public:
    void process(cv::Mat img);
    void handleInput(std::string command);

private:
    void clusterPoles(std::vector<int> lineXCoords);

    const int ANGLE = 25;
    float averageXCoord = 0;
    // Used for finding the orange color, subject to change
    int _lowHue = 0;
    int _highHue = 179;
    int _lowSaturation = 0;
    int _highSaturation = 133;
    int _lowValue = 0;
    int _highValue = 255;

    int rightGateX;
    int leftGateX;
};
