#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

Point interpolateBoundary(const std::vector<Point>& curve, float t) {
    Point result{0.0f, 0.0f, 0.0f};

    for (const auto& point : curve) {
        result.x += point.x * t;
        result.y += point.y * t;
        result.z += point.z * t;
    }

    return result;
}

Point interpolateDiagonal(const std::vector<Point>& curve1, const std::vector<Point>& curve2, float t) {
    Point result{0.0f, 0.0f, 0.0f};

    for (size_t i = 0; i < curve1.size(); ++i) {
        result.x += curve1[i].x * (1.0f - t) + curve2[i].x * t;
        result.y += curve1[i].y * (1.0f - t) + curve2[i].y * t;
        result.z += curve1[i].z * (1.0f - t) + curve2[i].z * t;
    }

    return result;
}

Point evaluateCoonsPatch(const std::vector<Point>& curveU0, const std::vector<Point>& curveU1,
                         const std::vector<Point>& curveV0, const std::vector<Point>& curveV1,
                         float u, float v) {
    Point boundary1 = interpolateBoundary(curveU0, u);
    Point boundary2 = interpolateBoundary(curveU1, u);
    Point boundary3 = interpolateBoundary(curveV0, v);
    Point boundary4 = interpolateBoundary(curveV1, v);

    Point diagonal1 = interpolateDiagonal(curveU0, curveV0, u);
    Point diagonal2 = interpolateDiagonal(curveU1, curveV1, u);

    float blendU = (1.0f - v) * u;
    float blendV = v * (1.0f - u);

    Point result{0.0f, 0.0f, 0.0f};

    result.x = boundary1.x * (1.0f - u) + boundary2.x * u + boundary3.x * (1.0f - v) + boundary4.x * v
               + diagonal1.x * blendU + diagonal2.x * blendV;
    result.y = boundary1.y * (1.0f - u) + boundary2.y * u + boundary3.y * (1.0f - v) + boundary4.y * v
               + diagonal1.y * blendU + diagonal2.y * blendV;
    result.z = boundary1.z * (1.0f - u) + boundary2.z * u + boundary3.z * (1.0f - v) + boundary4.z * v
               + diagonal1.z * blendU + diagonal2.z * blendV;

    return result;
}

std::vector<std::vector<Point>> generateCoonsPatch(const std::vector<Point>& curveU0, const std::vector<Point>& curveU1,
                                                   const std::vector<Point>& curveV0, const std::vector<Point>& curveV1,
                                                   int numPointsU, int numPointsV) {
    std::vector<std::vector<Point>> surfacePoints;

    float uStep = 1.0f / numPointsU;
    float vStep = 1.0f / numPointsV;

    for (int i = 0; i <= numPointsU; ++i) {
        float u = i * uStep;

        std::vector<Point> rowPoints;

        for (int j = 0; j <= numPointsV; ++j) {
            float v = j * vStep;

            Point point = evaluateCoonsPatch(curveU0, curveU1, curveV0, curveV1, u, v);
            rowPoints.push_back(point);
        }

        surfacePoints.push_back(rowPoints);
    }

    return surfacePoints;
}

int main() {
    std::vector<Point> curveU0 = { {0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0} };
    std::vector<Point> curveU1 = { {0, 1, 1}, {1, 2, 1}, {2, -2, 1}, {3, -1, 1} };
    std::vector<Point> curveV0 = { {0, 0, 0}, {0, 1, 1}, {0, 2, 2}, {0, 3, 3} };
    std::vector<Point> curveV1 = { {3, 0, 0}, {3, -1, 1}, {3, -2, 2}, {3, -3, 3} };
    int numPointsU = 10;
    int numPointsV = 10;

    std::vector<std::vector<Point>> surfacePoints = generateCoonsPatch(curveU0, curveU1, curveV0, curveV1, numPointsU, numPointsV);
    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
        }
    }

    return 0;
}
