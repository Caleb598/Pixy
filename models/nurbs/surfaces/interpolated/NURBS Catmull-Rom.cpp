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

    float blend1 = -0.5f * t3 + t2 - 0.5f * t;
    float blend2 = 1.5f * t3 - 2.5f * t2 + 1.0f;
    float blend3 = -1.5f * t3 + 2.0f * t2 + 0.5f * t;
    float blend4 = 0.5f * t3 - 0.5f * t2;

    Point interpolatedPoint;
    interpolatedPoint.x = p0.x * blend1 + p1.x * blend2 + p2.x * blend3 + p3.x * blend4;
    interpolatedPoint.y = p0.y * blend1 + p1.y * blend2 + p2.y * blend3 + p3.y * blend4;
    interpolatedPoint.z = p0.z * blend1 + p1.z * blend2 + p2.z * blend3 + p3.z * blend4;

    return interpolatedPoint;
}

std::vector<std::vector<Point>> generateCatmullRomSurface(const std::vector<std::vector<Point>>& controlPoints, int numPointsU, int numPointsV) {
    std::vector<std::vector<Point>> surfacePoints;

    int n = controlPoints.size() - 1;
    int m = controlPoints[0].size() - 1;

    float uStep = 1.0f / numPointsU;
    float vStep = 1.0f / numPointsV;

    for (int i = 0; i < numPointsU; ++i) {
        float u = i * uStep;

        std::vector<Point> rowPoints;

        for (int j = 0; j < numPointsV; ++j) {
            float v = j * vStep;

            int segU = static_cast<int>(u * n);
            int segV = static_cast<int>(v * m);

            float tU = (u * n) - segU;
            float tV = (v * m) - segV;

            Point p0 = controlPoints[segU][segV];
            Point p1 = controlPoints[segU][segV + 1];
            Point p2 = controlPoints[segU + 1][segV + 1];
            Point p3 = controlPoints[segU + 1][segV];

            Point point = interpolateCatmullRom(p0, p1, p2, p3, tV);
            rowPoints.push_back(point);
        }

        surfacePoints.push_back(rowPoints);
    }

    return surfacePoints;
}

int main() {
    std::vector<std::vector<Point>> controlPoints = {
        {{0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0}},
        {{0, 1, 1}, {1, 2, 1}, {2, -2, 1}, {3, -1, 1}},
        {{0, 2, 2}, {1, 3, 2}, {2, -3, 2}, {3, -2, 2}},
        {{0, 3, 3}, {1, 4, 3}, {2, -4, 3}, {3, -3, 3}}
    };
    int numPointsU = 100;
    int numPointsV = 100;

    std::vector<std::vector<Point>> surfacePoints = generateCatmullRomSurface(controlPoints, numPointsU, numPointsV);
    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
        }
    }

    return 0;
}
