#include "GateDetector.h"

typedef std::tuple<int, int, std::vector<cv::Point>> ContourTuple;
std::pair<int, int> getMinMaxX(std::vector<cv::Point> contour);
json readHsvJson();

GateDetector::GateDetector() {
    refreshHsv();
}

void GateDetector::process(cv::Mat img)
{
    cv::Mat grayImg = Capture::grayscale(img);
    cv::Mat thresholdedImg;

    // Only considers pixels in the correct color range
    cv::inRange(grayImg, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), thresholdedImg);

    // Morphological opening (removes small objects from the foreground)
    cv::erode(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    // Morphological closing (removes small holes from the foreground)
    cv::dilate(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(thresholdedImg, thresholdedImg, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::Canny(thresholdedImg, thresholdedImg, 50, 200, 3);

    std::vector<std::vector<cv::Point>> rawContours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresholdedImg, rawContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    std::vector<ContourTuple> contours;
    for (auto contour : rawContours) {
        auto xPair = getMinMaxX(contour);
        if (xPair.first < 10 && xPair.second > frameWidth-10) continue;
        auto contourTuple = std::make_tuple(xPair.first, xPair.second, contour);
        contours.push_back(contourTuple);
    }

    std::sort(contours.begin(), contours.end(), [](ContourTuple left, ContourTuple right){
        int leftVal, rightVal;
        std::tie(leftVal, std::ignore, std::ignore) = left;
        std::tie(rightVal, std::ignore, std::ignore) = right;
        return leftVal < rightVal;
    });

    int currMax = 0;
    std::vector<std::vector<cv::Point>> clusters;
    for (auto i = 0u; i < contours.size(); i++) {
        int minX, maxX;
        std::vector<cv::Point> contour;
        std::tie(minX, maxX, contour) = contours[i];
        if (i == 0 || minX > currMax) {
            clusters.push_back(std::vector<cv::Point>());
        }
        for (auto m = 0u; m < contour.size(); m++) {
            clusters[clusters.size()-1].push_back(contour[m]);
        }
        if(currMax < maxX) currMax = maxX;

    }

    std::vector<cv::RotatedRect> rects;
    for (auto cluster : clusters) {
        std::vector<cv::Point> hull;
        cv::convexHull(cv::Mat(cluster), hull);
        auto rect = cv::minAreaRect(hull);
        rects.push_back(rect);
    }

    auto largestArea = 0u;
    for (auto rect : rects) {
        if (rect.size.area() > largestArea) largestArea = (unsigned int)rect.size.area();
    }

    json poles;
    for (auto rect : rects) {
        if (rect.size.area()*3 < largestArea) continue;
        cv::Point2f points[4]; rect.points(points);
        json pole;
        for (auto point : points) {
            json pointJson;
            pointJson["X"] = point.x;
            pointJson["Y"] = point.y;
            pole.push_back(pointJson);
        }
        poles.push_back(pole);
    }

    cv::Mat cdst;

    // Simplify the color
    cv::cvtColor(thresholdedImg, cdst, CV_GRAY2BGR);

    for (auto pole : poles) {
        for (auto j = 0u; j < 4; j++) {
            auto pointA = cv::Point(pole[j]["X"], pole[j]["Y"]);
            auto pointB = cv::Point(pole[(j+1)%4]["X"], pole[(j+1)%4]["Y"]);
            cv::line(cdst, pointA, pointB, cv::Scalar(255,0,0));
        }
    }

    // If you want to save images
    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", cdst);

    // If you want to show the image on screen (debugging only)
    cv::imshow("poles", cdst);

    // Must stay in if you are debugging
    cv::waitKey(30);

    poles_ = poles;
}

std::pair<int, int> getMinMaxX(std::vector<cv::Point> contour) {
    if (contour.size() == 0) return std::make_pair(-1,-1);
    int minX = contour[0].x, maxX = contour[0].x;
    for (auto i = 1u; i < contour.size(); i++) {
            int currX = contour[i].x;
            if (currX < minX) minX = currX;
            else if (currX > maxX) maxX = currX;
        }
    return std::make_pair(minX, maxX);
}

void GateDetector::handleInput(std::string command)
{
    Capture::handleInput(command);

    if(command.compare("getPoleCount") == 0)
    {
        std::cout << poles_.size() << std::endl;
    }
}

void GateDetector::refreshHsv() {
    setHsvValues(readHsvJson());
}

json readHsvJson() {
    auto fin = std::fstream("PoleHsv.json");
    json hsvJson;
    fin >> hsvJson;
    fin.close();
    return hsvJson;
}

void GateDetector::setHsvValues(json hsvJson) {
    _lowHue = hsvJson["MinHue"];
    _highHue = hsvJson["MaxHue"];
    _lowSaturation = hsvJson["MinSaturation"];
    _highSaturation = hsvJson["MaxSaturation"];
    _lowValue = hsvJson["MinValue"];
    _highValue = hsvJson["MaxValue"];
}
