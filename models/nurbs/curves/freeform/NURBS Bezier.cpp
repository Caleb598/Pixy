#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
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

std::vector<Point> evaluateNURBSCurve(const std::vector<Point>& controlPoints, const std::vector<float>& weights,
                                     const std::vector<float>& knotVector, int degree, int parameterRange = 100) {
    std::vector<Point> curvePoints;

    for (int i = 0; i <= parameterRange; i++) {
        float t = static_cast<float>(i) / parameterRange;

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        for (int j = 0; j < controlPoints.size(); j++) {
            float basis = calculateBasis(knotVector, degree, j, t);
            x += controlPoints[j].x * weights[j] * basis;
            y += controlPoints[j].y * weights[j] * basis;
            z += controlPoints[j].z * weights[j] * basis;
        }

        curvePoints.push_back({x, y, z});
    }

    return curvePoints;
}

int main() {
    std::vector<Point> controlPoints = {{0, 0, 0}, {1, 3, 0}, {4, 2, 0}, {6, 7, 0}, {8, 4, 0}};
    std::vector<float> weights = {1, 2, 1, 1, 3};
    std::vector<float> knotVector = {0, 0, 0, 0.5, 1, 1, 1};
    int degree = 3;

    std::vector<Point> curvePoints = evaluateNURBSCurve(controlPoints, weights, knotVector, degree);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
