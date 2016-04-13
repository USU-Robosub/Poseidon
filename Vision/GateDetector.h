#include "Capture.h"

class GateDetector : public Capture
{
public:
    GateDetector();
    void process(cv::Mat img);
    void handleInput(int n);
private:
    // Used for finding the orange color, subject to change
    int _lowHue;
    int _highHue;
    int _lowSaturation;
    int _highSaturation;
    int _lowValue;
    int _highValue;

    std::list<float> _leftXs;
    std::list<float> _leftYs;
    std::list<float> _rightXs;
    std::list<float> _rightYs;

    int QUEUE_SIZE = 20;
};
