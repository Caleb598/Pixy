#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

Point interpolateCatmullRom(const Point& p0, const Point& p1, const Point& p2, const Point& p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;

    float b0 = -0.5f * t3 + t2 - 0.5f * t;
    float b1 = 1.5f * t3 - 2.5f * t2 + 1.0f;
    float b2 = -1.5f * t3 + 2.0f * t2 + 0.5f * t;
    float b3 = 0.5f * t3 - 0.5f * t2;

    Point interpolatedPoint;
    interpolatedPoint.x = p0.x * b0 + p1.x * b1 + p2.x * b2 + p3.x * b3;
    interpolatedPoint.y = p0.y * b0 + p1.y * b1 + p2.y * b2 + p3.y * b3;
    interpolatedPoint.z = p0.z * b0 + p1.z * b1 + p2.z * b2 + p3.z * b3;

    return interpolatedPoint;
}

std::vector<Point> generateCatmullRomCurve(const std::vector<Point>& controlPoints, int numPoints, bool loop = false) {
    std::vector<Point> curvePoints;

    int numSegments = controlPoints.size() - 1;
    int startIndex = loop ? 0 : 1;
    int endIndex = loop ? numSegments : numSegments - 1;

    for (int i = startIndex; i <= endIndex; i++) {
        Point p0, p1, p2, p3;

        if (loop) {
            p0 = controlPoints[(i + numSegments - 1) % numSegments];
            p1 = controlPoints[i];
            p2 = controlPoints[(i + 1) % numSegments];
            p3 = controlPoints[(i + 2) % numSegments];
        } else {
            p0 = controlPoints[i - 1];
            p1 = controlPoints[i];
            p2 = controlPoints[i + 1];
            p3 = controlPoints[i + 2];
        }

        for (int j = 0; j < numPoints; j++) {
            float t = static_cast<float>(j) / numPoints;
            Point point = interpolateCatmullRom(p0, p1, p2, p3, t);
            curvePoints.push_back(point);
        }
    }

    return curvePoints;
}

int main() {
    std::vector<Point> controlPoints = {{0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0}};
    int numPoints = 100;
    bool loop = false;

    std::vector<Point> curvePoints = generateCatmullRomCurve(controlPoints, numPoints, loop);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
