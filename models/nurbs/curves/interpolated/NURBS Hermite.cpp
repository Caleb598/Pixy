#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

struct Tangent {
    float dx;
    float dy;
    float dz;
};

Point interpolateHermite(const Point& p0, const Point& p1, const Tangent& t0, const Tangent& t1, float t) {
    float t2 = t * t;
    float t3 = t2 * t;

    float h0 = 2 * t3 - 3 * t2 + 1;
    float h1 = -2 * t3 + 3 * t2;
    float h2 = t3 - 2 * t2 + t;
    float h3 = t3 - t2;

    Point interpolatedPoint;
    interpolatedPoint.x = h0 * p0.x + h1 * p1.x + h2 * t0.dx + h3 * t1.dx;
    interpolatedPoint.y = h0 * p0.y + h1 * p1.y + h2 * t0.dy + h3 * t1.dy;
    interpolatedPoint.z = h0 * p0.z + h1 * p1.z + h2 * t0.dz + h3 * t1.dz;

    return interpolatedPoint;
}

std::vector<Point> generateHermiteCurve(const std::vector<Point>& controlPoints, const std::vector<Tangent>& tangents, int numPoints) {
    std::vector<Point> curvePoints;

    int numSegments = controlPoints.size() - 1;

    for (int i = 0; i < numSegments; i++) {
        const Point& p0 = controlPoints[i];
        const Point& p1 = controlPoints[i + 1];
        const Tangent& t0 = tangents[i];
        const Tangent& t1 = tangents[i + 1];

        for (int j = 0; j < numPoints; j++) {
            float t = static_cast<float>(j) / numPoints;
            Point point = interpolateHermite(p0, p1, t0, t1, t);
            curvePoints.push_back(point);
        }
    }

    return curvePoints;
}

int main() {
    std::vector<Point> controlPoints = {{0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0}};
    std::vector<Tangent> tangents = {{0.5, 0, 0}, {-1, 0.5, 0}, {1, -0.5, 0}, {-0.5, 0, 0.5}};
    int numPoints = 100;

    std::vector<Point> curvePoints = generateHermiteCurve(controlPoints, tangents, numPoints);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
