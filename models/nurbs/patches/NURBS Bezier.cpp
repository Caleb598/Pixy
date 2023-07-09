#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

struct ControlPoint {
    Point point;
    float weight;
};

float calculateBasis(const std::vector<float>& knotVector, int degree, int i, float t) {
    if (degree == 0) {
        if (knotVector[i] <= t && t < knotVector[i + 1]) {
            return 1.0f;
        }
        return 0.0f;
    }

    float basis1 = 0.0f;
    float basis2 = 0.0f;

    if (knotVector[i + degree] != knotVector[i]) {
        basis1 = (t - knotVector[i]) / (knotVector[i + degree] - knotVector[i]) * calculateBasis(knotVector, degree - 1, i, t);
    }

    if (knotVector[i + degree + 1] != knotVector[i + 1]) {
        basis2 = (knotVector[i + degree + 1] - t) / (knotVector[i + degree + 1] - knotVector[i + 1]) * calculateBasis(knotVector, degree - 1, i + 1, t);
    }

    return basis1 + basis2;
}

Point evaluateNURBSBezierPatch(const std::vector<std::vector<ControlPoint>>& controlPoints,
                               const std::vector<float>& knotVectorU, int degreeU,
                               const std::vector<float>& knotVectorV, int degreeV,
                               float u, float v) {
    int n = controlPoints.size() - 1;
    int m = controlPoints[0].size() - 1;

    Point result{0.0f, 0.0f, 0.0f};
    float weightSum = 0.0f;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            float blendU = calculateBasis(knotVectorU, degreeU, i, u);
            float blendV = calculateBasis(knotVectorV, degreeV, j, v);
            float weight = controlPoints[i][j].weight;

            result.x += controlPoints[i][j].point.x * blendU * blendV * weight;
            result.y += controlPoints[i][j].point.y * blendU * blendV * weight;
            result.z += controlPoints[i][j].point.z * blendU * blendV * weight;

            weightSum += blendU * blendV * weight;
        }
    }

    if (weightSum != 0.0f) {
        result.x /= weightSum;
        result.y /= weightSum;
        result.z /= weightSum;
    }

    return result;
}

std::vector<std::vector<Point>> generateNURBSBezierPatch(const std::vector<std::vector<ControlPoint>>& controlPoints,
                                                         const std::vector<float>& knotVectorU, int degreeU,
                                                         const std::vector<float>& knotVectorV, int degreeV,
                                                         int numPointsU, int numPointsV) {
    std::vector<std::vector<Point>> surfacePoints;

    float uStep = (knotVectorU.back() - knotVectorU[degreeU]) / numPointsU;
    float vStep = (knotVectorV.back() - knotVectorV[degreeV]) / numPointsV;

    for (int i = 0; i <= numPointsU; ++i) {
        float u = knotVectorU[degreeU] + i * uStep;

        std::vector<Point> rowPoints;

        for (int j = 0; j <= numPointsV; ++j) {
            float v = knotVectorV[degreeV] + j * vStep;

            Point point = evaluateNURBSBezierPatch(controlPoints, knotVectorU, degreeU, knotVectorV, degreeV, u, v);
            rowPoints.push_back(point);
        }

        surfacePoints.push_back(rowPoints);
    }

    return surfacePoints;
}

int main() {
    std::vector<std::vector<ControlPoint>> controlPoints = {
        {{ {0, 0, 0}, 1 }, { {1, 1, 0}, 1 }, { {2, -1, 0}, 1 }, { {3, 0, 0}, 1 }},
        {{ {0, 1, 1}, 1 }, { {1, 2, 1}, 1 }, { {2, -2, 1}, 1 }, { {3, -1, 1}, 1 }},
        {{ {0, 2, 2}, 1 }, { {1, 3, 2}, 1 }, { {2, -3, 2}, 1 }, { {3, -2, 2}, 1 }},
        {{ {0, 3, 3}, 1 }, { {1, 4, 3}, 1 }, { {2, -4, 3}, 1 }, { {3, -3, 3}, 1 }}
    };

    std::vector<float> knotVectorU = {0, 0, 0, 0, 1, 1, 1, 1};
    std::vector<float> knotVectorV = {0, 0, 0, 0, 1, 1, 1, 1};
    int degreeU = 3;
    int degreeV = 3;
    int numPointsU = 10;
    int numPointsV = 10;

    std::vector<std::vector<Point>> surfacePoints = generateNURBSBezierPatch(controlPoints, knotVectorU, degreeU, knotVectorV, degreeV, numPointsU, numPointsV);
    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
        }
    }

    return 0;
}
