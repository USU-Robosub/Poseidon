#include "GateDetector.h"

typedef std::vector<std::vector<cv::Point>> PointClusters;
typedef std::vector<std::vector<Contour>> ContourClusters;

json readHsvJson();

std::vector<Contour> findContoursInImage(cv::Mat& thresholdedImg, int frameWidth);
Contour getMinMax(std::vector<cv::Point>& contour);
void sortContoursByX(std::vector<Contour>& contours);
ContourClusters clusterContours(std::vector<Contour>& contours);
void sortContoursByY(std::vector<Contour>& contours);
PointClusters removeReflections(ContourClusters& contourClusters);
std::vector<cv::RotatedRect> findRectanglesAroundClusters(PointClusters& clusters);
unsigned int findAreaOfLargestRectangles(std::vector<cv::RotatedRect>& rectangles);

#ifdef DEBUG
void showDebugFeed(cv::Mat thresholdedImg, json poles, std::vector<Contour>& contours, PointClusters clusters,
                   int frameWidth, int frameHeight);
void showRectangles(json poles, cv::Mat debugFeed, int frameWidth, int frameHeight);
void showContours(const std::vector<Contour>& contours, const cv::Mat& debugFeed);
void showClusters(const PointClusters& clusters, const cv::Mat& debugFeed);
#endif

GateDetector::GateDetector() {
    refreshHsv();
}

void GateDetector::refreshHsv() {
    setHsvValues(readHsvJson());
}

json readHsvJson() {
    std::fstream fin;
    fin.open("PoleHsv.json");
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
    auto grayImg = Capture::grayScale(img);
    auto thresholdedImg = thresholdImage_(grayImg);
    auto contours = findContoursInImage(thresholdedImg, frameWidth);
    sortContoursByX(contours);
    auto clusters = clusterContours(contours);
    auto trimmedClusters = removeReflections(clusters);
    auto rectangles = findRectanglesAroundClusters(trimmedClusters);
    auto poles = rectanglesToPoles_(rectangles);
    poles_ = poles;
#ifdef DEBUG
    showDebugFeed(thresholdedImg, poles_, contours, trimmedClusters, frameWidth, frameHeight);
#endif
}

cv::Mat GateDetector::thresholdImage_(cv::Mat& image) {
    cv::Mat thresholdedImg;

    // Only considers pixels in the correct color range
    if (_lowHue > _highHue) {
        cv::Mat lower, upper;
        cv::inRange(image, cv::Scalar(0, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), lower);
        cv::inRange(image, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(180, _highSaturation, _highValue), upper);
        thresholdedImg = lower | upper;
    }
    else {
        cv::inRange(image, cv::Scalar(_lowHue, _lowSaturation, _lowValue), cv::Scalar(_highHue, _highSaturation, _highValue), thresholdedImg);
    }

    // Morphological opening (removes small objects from the foreground)
    cv::erode(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::dilate(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

    // Morphological closing (removes small holes from the foreground)
    cv::dilate(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::erode(thresholdedImg, thresholdedImg, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    cv::Canny(thresholdedImg, thresholdedImg, 50, 200, 3);
    return thresholdedImg;
}

std::vector<Contour> findContoursInImage(cv::Mat& thresholdedImg, int frameWidth) {
    PointClusters rawContours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresholdedImg, rawContours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<Contour> contours;
    for (auto contour : rawContours) {
        auto contourStruct = getMinMax(contour);
        if (contourStruct.MinX < 10 && contourStruct.MaxX > frameWidth - 10) continue;
        contours.push_back(contourStruct);
    }
    return contours;
}

Contour getMinMax(std::vector<cv::Point>& contour) {
    if (contour.size() == 0) return Contour{-1,-1,-1,-1,contour};
    int minX = contour[0].x, maxX = contour[0].x;
    int minY = contour[0].y, maxY = contour[0].y;
    for (auto i = 1u; i < contour.size(); i++) {
        int currX = contour[i].x;
        int currY = contour[i].y;
        if (minX > currX) minX = currX;
        if (maxX < currX) maxX = currX;
        if (minY > currY) minY = currY;
        if (maxY < currY) maxY = currY;
    }
    return Contour{minX, maxX, minY, maxY, contour};
}

void sortContoursByX(std::vector<Contour>& contours) {
    std::sort(contours.begin(), contours.end(), [](Contour left, Contour right){
        return left.MinX < right.MinX;
    });
}

ContourClusters clusterContours(std::vector<Contour>& contours) {
    int currMax = -1;
    ContourClusters clusters;
    for (auto i = 0u; i < contours.size(); i++) {
        auto contour = contours[i];
        if (i == 0 || contour.MinX > currMax) {
            clusters.push_back(std::vector<Contour>());
        }
        if(currMax < contour.MaxX) currMax = contour.MaxX;
        clusters[clusters.size()-1].push_back(contour);
    }
    return clusters;
}

PointClusters removeReflections(ContourClusters& contourClusters) {
    PointClusters trimmedClusters;
    trimmedClusters.reserve(contourClusters.size());
    for (auto cluster : contourClusters) {
        sortContoursByY(cluster);
        std::vector<cv::Point> pointCluster;
        for (auto point : cluster[0].Contour) {
            pointCluster.push_back(point);
        }
        auto maxY = cluster[0].MaxY;
        auto minX = cluster[0].MinX; auto maxX = cluster[0].MaxX;
        for (auto i = 1u; i < cluster.size(); i++) {
            auto minY = maxY - (maxX-minX)*5;
            if (cluster[i].MaxY > (minY+maxY)/2 || (cluster[i].MinY+cluster[i].MaxY)/2 > minY) {
                if (cluster[i].MinX < minX) minX = cluster[i].MinX;
                if (cluster[i].MaxX > maxX) maxX = cluster[i].MaxX;
                for (auto p : cluster[i].Contour) {
                    pointCluster.push_back(p);
                }
            }
        }
        trimmedClusters.push_back(pointCluster);
    }
    return trimmedClusters;
}

void sortContoursByY(std::vector<Contour>& contours) {
    std::sort(contours.begin(), contours.end(), [](Contour left, Contour right){
        return left.MaxY > right.MaxY;
    });
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

json GateDetector::rectanglesToPoles_(std::vector<cv::RotatedRect>& rectangles) {
    auto largestArea = findAreaOfLargestRectangles(rectangles);
    json poles = json::array();
    for (auto rect : rectangles) {
        if (rect.size.area()*3 < largestArea) continue;
        if (rect.size.height*6 < rect.size.width) continue;
        auto pole = rectangleToPole_(rect);
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

    else if(command.compare("refreshHsv") == 0) {
        refreshHsv();
        out << "{\"Type\":\"RefreshHsv\"}" << std::endl;
    }
}

#ifdef DEBUG
void showDebugFeed(cv::Mat thresholdedImg, json poles, std::vector<Contour>& contours, PointClusters clusters,
                   int frameWidth, int frameHeight) {
    cv::Mat debugFeed;

    // Simplify the color
    cvtColor(thresholdedImg, debugFeed, CV_GRAY2BGR);
    showContours(contours, debugFeed);
    showClusters(clusters, debugFeed);
    showRectangles(poles, debugFeed, frameWidth, frameHeight);

    // If you want to save images
    //cv::imwrite("thresh.jpg", thresholdedImg);
    //cv::imwrite("lines.jpg", debugFeed);

    // If you want to show the image on screen (debugging only)
    imshow("poles", debugFeed);

    cv::waitKey(30);
}

void showContours(const std::vector<Contour>& contours, const cv::Mat& debugFeed) {
    for (auto contourStruct : contours) {
        auto contour = contourStruct.Contour;
        if (contour.size() < 2) continue;
        for (auto i = 1u; i < contour.size(); i++) {
            auto point1 = contour[i];
            auto point2 = contour[(i+1)%contour.size()];
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

void showRectangles(json poles, cv::Mat debugFeed, int frameWidth, int frameHeight) {
    for (auto pole : poles) {
        for (auto i = 0u; i < 4; i++) {
            auto pointA = cv::Point((int)pole[i]["X"]+frameWidth/2, -(int)pole[i]["Y"]+frameHeight/2);
            auto pointB = cv::Point((int)pole[(i + 1) % 4]["X"]+frameWidth/2, -(int)pole[(i + 1) % 4]["Y"]+frameHeight/2);
            line(debugFeed, pointA, pointB, cv::Scalar(255, 0, 0));
        }
    }
}

#endif
