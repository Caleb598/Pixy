#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

struct Vector {
    float x;
    float y;
    float z;
};

Point interpolateHermite(const Point& p0, const Point& p1, const Vector& v0, const Vector& v1, float t) {
    float t2 = t * t;
    float t3 = t2 * t;

    float blend1 = 2.0f * t3 - 3.0f * t2 + 1.0f;
    float blend2 = -2.0f * t3 + 3.0f * t2;
    float blend3 = t3 - 2.0f * t2 + t;
    float blend4 = t3 - t2;

    Point interpolatedPoint;
    interpolatedPoint.x = p0.x * blend1 + p1.x * blend2 + v0.x * blend3 + v1.x * blend4;
    interpolatedPoint.y = p0.y * blend1 + p1.y * blend2 + v0.y * blend3 + v1.y * blend4;
    interpolatedPoint.z = p0.z * blend1 + p1.z * blend2 + v0.z * blend3 + v1.z * blend4;

    return interpolatedPoint;
}

std::vector<std::vector<Point>> generateHermiteSurface(const std::vector<std::vector<Point>>& controlPoints,
                                                       const std::vector<std::vector<Vector>>& tangentVectorsU,
                                                       const std::vector<std::vector<Vector>>& tangentVectorsV,
                                                       int numPointsU, int numPointsV) {
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
            Vector v0 = tangentVectorsU[segU][segV];
            Vector v1 = tangentVectorsU[segU][segV + 1];

            Point point = interpolateHermite(p0, p1, v0, v1, tV);
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
    
    std::vector<std::vector<Vector>> tangentVectorsU = {
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}},
        {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}}
    };
    
    std::vector<std::vector<Vector>> tangentVectorsV = {
        {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
        {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
        {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
        {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}}
    };

    int numPointsU = 100;
    int numPointsV = 100;

    std::vector<std::vector<Point>> surfacePoints = generateHermiteSurface(controlPoints, tangentVectorsU, tangentVectorsV, numPointsU, numPointsV);
    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
        }
    }

    return 0;
}
