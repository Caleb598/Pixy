#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

Point evaluateBezierSurface(const std::vector<std::vector<Point>>& controlPoints, float u, float v) {
    int n = controlPoints.size() - 1;
    int m = controlPoints[0].size() - 1;

    Point result{0.0f, 0.0f, 0.0f};

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            float blendU = 1.0f;
            float blendV = 1.0f;

            for (int k = 0; k <= n; ++k) {
                if (k != i) {
                    blendU *= (u - static_cast<float>(k)) / (static_cast<float>(i) - static_cast<float>(k));
                }
            }

            for (int k = 0; k <= m; ++k) {
                if (k != j) {
                    blendV *= (v - static_cast<float>(k)) / (static_cast<float>(j) - static_cast<float>(k));
                }
            }

            result.x += controlPoints[i][j].x * blendU * blendV;
            result.y += controlPoints[i][j].y * blendU * blendV;
            result.z += controlPoints[i][j].z * blendU * blendV;
        }
    }

    return result;
}

std::vector<std::vector<Point>> generateBezierControlPointSurface(const std::vector<std::vector<Point>>& controlPoints, int numPointsU, int numPointsV) {
    std::vector<std::vector<Point>> surfacePoints;

    float uStep = 1.0f / numPointsU;
    float vStep = 1.0f / numPointsV;

    for (int i = 0; i <= numPointsU; ++i) {
        float u = i * uStep;

        std::vector<Point> rowPoints;

        for (int j = 0; j <= numPointsV; ++j) {
            float v = j * vStep;

            Point point = evaluateBezierSurface(controlPoints, u, v);
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
    int numPointsU = 10;
    int numPointsV = 10;

    std::vector<std::vector<Point>> surfacePoints = generateBezierControlPointSurface(controlPoints, numPointsU, numPointsV);
    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
        }
    }

    return 0;
}
