#include "GateDetector.h"

typedef std::vector<std::vector<cv::Point>> PointClusters;
typedef std::tuple<int, int, std::vector<cv::Point>> ContourTuple;

json readHsvJson();

std::vector<ContourTuple> findContoursInImage(cv::Mat& thresholdedImg, int frameWidth);
std::pair<int, int> getMinMaxX(std::vector<cv::Point>& contour);
void sortContours(std::vector<ContourTuple>& contours);
PointClusters clusterContours(std::vector<ContourTuple>& contours);
std::vector<cv::RotatedRect> findRectanglesAroundClusters(PointClusters& clusters);
json rectanglesToPoles(std::vector<cv::RotatedRect>& rectangles);
json rectangleToPole(cv::RotatedRect& rectangle);
unsigned int findAreaOfLargestRectangles(std::vector<cv::RotatedRect>& rectangles);

#ifdef DEBUG
void showDebugFeed(cv::Mat& thresholdedImg, json& poles, std::vector<ContourTuple>& contourTuples, PointClusters& clusters);
void showRectangles(const json& poles, const cv::Mat& debugFeed);
void showContours(const std::vector<ContourTuple>& contourTuples, const cv::Mat& debugFeed);
void showClusters(const PointClusters& clusters, const cv::Mat& debugFeed);
#endif

GateDetector::GateDetector() {
    refreshHsv();
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

void GateDetector::process(cv::Mat& img)
{
    auto grayImg = Capture::grayscale(img);
    auto thresholdedImg = thresholdImage(grayImg);
    auto contours = findContoursInImage(thresholdedImg, frameWidth);
    sortContours(contours);
    auto clusters = clusterContours(contours);
    auto rectangles = findRectanglesAroundClusters(clusters);
    auto poles = rectanglesToPoles(rectangles);
    poles_ = poles;
#ifdef DEBUG
    showDebugFeed(thresholdedImg, poles_, contours, clusters);
#endif
}

cv::Mat GateDetector::thresholdImage(cv::Mat& image) {
    cv::Mat thresholdedImg;

    // Only considers pixels in the correct color range
    inRange(image, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), thresholdedImg);

    // Morphological opening (removes small objects from the foreground)
    erode(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    dilate(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    // Morphological closing (removes small holes from the foreground)
    dilate(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    erode(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    Canny(thresholdedImg, thresholdedImg, 50, 200, 3);
    return thresholdedImg;
}

std::vector<ContourTuple> findContoursInImage(cv::Mat& thresholdedImg, int frameWidth) {
    PointClusters rawContours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(thresholdedImg, rawContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<ContourTuple> contours;
    for (auto contour : rawContours) {
        auto xPair = getMinMaxX(contour);
        if (xPair.first < 10 && xPair.second > frameWidth - 10) continue;
        auto contourTuple = make_tuple(xPair.first, xPair.second, contour);
        contours.push_back(contourTuple);
    }
    return contours;
}

std::pair<int, int> getMinMaxX(std::vector<cv::Point>& contour) {
    if (contour.size() == 0) return std::make_pair(-1,-1);
    int minX = contour[0].x, maxX = contour[0].x;
    for (auto i = 1u; i < contour.size(); i++) {
        int currX = contour[i].x;
        if (minX > currX) minX = currX;
        if (maxX < currX) maxX = currX;
    }
    return std::make_pair(minX, maxX);
}

void sortContours(std::vector<ContourTuple>& contours) {
    std::sort(contours.begin(), contours.end(), [](ContourTuple left, ContourTuple right){
        int leftVal, rightVal;
        std::tie(leftVal, std::ignore, std::ignore) = left;
        std::tie(rightVal, std::ignore, std::ignore) = right;
        return leftVal < rightVal;
    });
}

PointClusters clusterContours(std::vector<ContourTuple>& contours) {
    int currMax = -1;
    PointClusters clusters;
    for (auto i = 0u; i < contours.size(); i++) {
        int minX, maxX;
        std::vector<cv::Point> contour;
        std::tie(minX, maxX, contour) = contours[i];
        if (i == 0 || minX > currMax) {
            clusters.push_back(std::vector<cv::Point>());
        }
        for (auto point : contour) {
            clusters[clusters.size()-1].push_back(point);
        }
        if(currMax < maxX) currMax = maxX;

    }
    return clusters;
}

std::vector<cv::RotatedRect> findRectanglesAroundClusters(PointClusters& clusters) {
    std::vector<cv::RotatedRect> rectangles;
    for (auto cluster : clusters) {
        std::vector<cv::Point> hull;
        convexHull(cv::Mat(cluster), hull);
        auto rect = minAreaRect(hull);
        rectangles.push_back(rect);
    }
    return rectangles;
}

json rectanglesToPoles(std::vector<cv::RotatedRect>& rectangles) {
    auto largestArea = findAreaOfLargestRectangles(rectangles);
    json poles;
    for (auto rect : rectangles) {
        if (rect.size.area()*3 < largestArea) continue;
        json pole = rectangleToPole(rect);
        poles.push_back(pole);
    }
    return poles;
}

unsigned int findAreaOfLargestRectangles(std::vector<cv::RotatedRect>& rectangles) {
    auto largestArea = 0u;
    for (auto rect : rectangles) {
        if (rect.size.area() > largestArea) largestArea = (unsigned int)rect.size.area();
    }
    return largestArea;
}

json rectangleToPole(cv::RotatedRect& rectangle) {
    cv::Point2f points[4]; rectangle.points(points);
    json pole;
    for (auto point : points) {
        json pointJson;
        pointJson["X"] = point.x;
        pointJson["Y"] = point.y;
        pole.push_back(pointJson);
    }
    return pole;
}

void GateDetector::handleInput(std::string command) {
    Capture::handleInput(command);

    if(command.compare("getPoleCount") == 0) {
        std::cout << poles_.size() << std::endl;
    }

    else if(command.compare("refreshHsv") == 0) {
        refreshHsv();
    }
}

#ifdef DEBUG
void showDebugFeed(cv::Mat& thresholdedImg, json& poles, std::vector<ContourTuple>& contourTuples, PointClusters& clusters) {
    cv::Mat debugFeed;

    // Simplify the color
    cvtColor(thresholdedImg, debugFeed, CV_GRAY2BGR);
    showContours(contourTuples, debugFeed);
    showClusters(clusters, debugFeed);
    showRectangles(poles, debugFeed);

    // If you want to save images
    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", debugFeed);

    // If you want to show the image on screen (debugging only)
    imshow("poles", debugFeed);

    cv::waitKey(30);
}

void showContours(const std::vector<ContourTuple>& contourTuples, const cv::Mat& debugFeed) {
    for (auto i = 0u; i < contourTuples.size(); i++) {
        std::vector<cv::Point> contour;
        int minX, maxX;
        tie(minX, maxX, contour) = contourTuples[i];
        if (contour.size() < 2) continue;
        for (auto j = 1u; j < contour.size(); j++) {
            auto point1 = contour[j];
            auto point2 = contour[(j+1)%contour.size()];
            line(debugFeed, point1, point2, cv::Scalar(0, 0, 255));
        }
    }
}

void showClusters(const PointClusters& clusters, const cv::Mat& debugFeed) {
    for (auto cluster : clusters) {
        std::vector<cv::Point> hull;
        convexHull(cv::Mat(cluster), hull);
        for (auto i = 0u; i < hull.size(); i++) {
            auto point1 = hull[i];
            auto point2 = hull[(i+1)%hull.size()];
            line(debugFeed, point1, point2, cv::Scalar(0, 255, 0));
        }
    }
}

void showRectangles(const json& poles, const cv::Mat& debugFeed) {
    for (auto pole : poles) {
        for (auto i = 0u; i < 4; i++) {
            auto pointA = cv::Point(pole[i]["X"], pole[i]["Y"]);
            auto pointB = cv::Point(pole[(i + 1) % 4]["X"], pole[(i + 1) % 4]["Y"]);
            line(debugFeed, pointA, pointB, cv::Scalar(255, 0, 0));
        }
    }
}

#endif
