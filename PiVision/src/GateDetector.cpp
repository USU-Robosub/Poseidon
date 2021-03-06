#include "GateDetector.h"

json readHsvJson();

#ifdef DEBUG
void showDebugFeed(json poles,
                   int frameWidth, int frameHeight);
#endif
void showRectangles(json poles, cv::Mat debugFeed, int frameWidth, int frameHeight);

GateDetector::GateDetector(){
    cv::Mat res = getSingleFrame();
    template_ = new cv::Mat[TEMPLATE_COUNT];
    template_[0] = cv::imread("../gate_template.png");
    scaleTemplates(res);
}

void GateDetector::scaleTemplates(cv::Mat camera) {
    float *scalex = new float[TEMPLATE_COUNT];
    float *scaley = new float[TEMPLATE_COUNT];
    for (int i = 0; i < TEMPLATE_COUNT; i++){
        scalex[i] = template_[i].cols / (float)SCALE_FACTOR_X;
        scaley[i] = template_[i].rows / (float)SCALE_FACTOR_Y;
    }
    for (int i = 0; i < TEMPLATE_COUNT; i++){
        cv::Size newSize;
        newSize.width = (int)(camera.cols * scalex[i]);
        newSize.height = (int)(camera.rows * scaley[i]);
        cv::resize(template_[i], template_[i], newSize, 0, 0, 1);
    }
    delete scalex;
    delete scaley;
}

void GateDetector::process(cv::Mat& img)
{
    auto rectangle = thresholdImage_(img, template_[0]);
    auto poles = rectangleToPole_(rectangle);
    poles_ = poles;
#ifdef DEBUG
    showDebugFeed(poles_, frameWidth, frameHeight);
#endif
}

cv::RotatedRect GateDetector::thresholdImage_(cv::Mat& image, cv::Mat& imageTemplate) {
    cv::Mat result;
    int resultRows = image.rows - imageTemplate.rows + 1;
    int resultCols = image.cols - imageTemplate.cols + 1;
    result.create(resultRows, resultCols, CV_32FC1);
    cv::matchTemplate(image, imageTemplate, result, CV_TM_SQDIFF);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;

    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    cv::rectangle(image, minLoc, cv::Point(minLoc.x + imageTemplate.cols, minLoc.y + imageTemplate.rows), cv::Scalar::all(0), 2, 8, 0);
    cv::Point center(maxLoc.x + imageTemplate.cols/2, maxLoc.y + imageTemplate.rows/2);
    return cv::RotatedRect(center, cv::Size2f(1, 1), 0);
}

json GateDetector::rectangleToPole_(cv::RotatedRect& rectangle) {
    cv::Point2f points[4]; rectangle.points(points);
    json pole;
    for (auto point : points) {
        auto pointJson = json{
                {"X", convertXCoordinate((int)point.x)},
                {"Y", convertYCoordinate((int)point.y)}
        };
        pole.push_back(pointJson);
    }
    return pole;
}

void GateDetector::handleInput(std::string command, std::ostream& out) {
    Capture::handleInput(command, out);

    if(command.compare("getPoleCoordinates") == 0) {
        auto poleCoords = json{
                {"Type",  "PoleCoordinates"},
                {"Poles", poles_}
        };
        out << poleCoords << std::endl;
    }
}

GateDetector::~GateDetector() {
    delete template_;
}

#ifdef DEBUG
void showDebugFeed(json pole,
                   int frameWidth, int frameHeight) {
    cv::Mat debugFeed;

    // Simplify the color
    showRectangles(pole, debugFeed, frameWidth, frameHeight);

    // If you want to save images
    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", debugFeed);

    // If you want to show the image on screen (debugging only)
    //imshow("poles", debugFeed);
}

void showRectangles(json pole, cv::Mat debugFeed, int frameWidth, int frameHeight) {
    for (auto i = 0u; i < 4; i++) {
        auto pointA = cv::Point((int)pole[i]["X"]+frameWidth/2, -(int)pole[i]["Y"]+frameHeight/2);
        auto pointB = cv::Point((int)pole[(i + 1) % 4]["X"]+frameWidth/2, -(int)pole[(i + 1) % 4]["Y"]+frameHeight/2);
        line(debugFeed, pointA, pointB, cv::Scalar(255, 0, 0));
    }
}

#endif
