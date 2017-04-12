//
// Created by Kyler Jensen on 4/12/17.
//

#include "../include/camera_frame_stream/CVFrameStream.h"
#include "../include/camera_frame/RGBCameraFrame.h"

using namespace slam;

CVFrameStream::CVFrameStream(int device) : videoCapture(device) {

}

const SmartPointer<ICameraFrame> slam::CVFrameStream::getFrame() {
    cv::Mat frame;
    videoCapture >> frame;
    return make_smart<RGBCameraFrame>(frame, std::chrono::steady_clock::now());
}
