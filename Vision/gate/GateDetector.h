#ifndef GATE_DETECTOR_H
#define GATE_DETECTOR_H

#include <iostream>
#include <list>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class GateDetector
{
private:
    // These are set for the orange of the gate
    unsigned short LOW_HUE;
    unsigned short HIGH_HUE;
    unsigned short LOW_SATURATION;
    unsigned short HIGH_SATURATION;
    unsigned short LOW_VALUE;
    unsigned short HIGH_VALUE;

    unsigned short QUEUE_SIZE;
    std::list<float> leftXs;
    std::list<float> rightXs;
    std::list<float> leftYs;
    std::list<float> rightYs;

    bool continueCapture;

    float rightGatePosition;
    float leftGatePosition;
    float centerPosition;
public:
    GateDetector();
    void startCapture();
    void stopCapture();
    float getRightGatePosition();
    float getLeftGatePosition();
    float getCenterPosition();
};

#endif
