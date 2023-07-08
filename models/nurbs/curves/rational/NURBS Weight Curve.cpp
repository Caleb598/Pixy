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

std::vector<Point> evaluateRationalNURBSCurve(const std::vector<ControlPoint>& controlPoints, const std::vector<float>& knotVector, int degree, int numPoints) {
    std::vector<Point> curvePoints;

    int n = controlPoints.size() - 1;

    for (int i = degree; i <= n; ++i) {
        for (int j = 0; j <= numPoints; ++j) {
            float t = static_cast<float>(j) / numPoints;

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            float weightSum = 0.0f;

            for (int k = 0; k <= degree; ++k) {
                float basis = calculateBasis(knotVector, degree, i - degree + k, t);
                float weightedBasis = basis * controlPoints[i - degree + k].weight;
                x += controlPoints[i - degree + k].point.x * weightedBasis;
                y += controlPoints[i - degree + k].point.y * weightedBasis;
                z += controlPoints[i - degree + k].point.z * weightedBasis;
                weightSum += weightedBasis;
            }

            // Divide by the sum of the weighted basis functions to account for the weights
            if (weightSum != 0.0f) {
                float invWeightSum = 1.0f / weightSum;
                x *= invWeightSum;
                y *= invWeightSum;
                z *= invWeightSum;
            }

            curvePoints.push_back({x, y, z});
        }
    }

    return curvePoints;
}

int main() {
    std::vector<ControlPoint> controlPoints = {
        {{0, 0, 0}, 1},
        {{1, 3, 0}, 2},
        {{4, 2, 0}, 1},
        {{6, 7, 0}, 1},
        {{8, 4, 0}, 3}
    };
    std::vector<float> knotVector = {0, 0, 0, 0.5, 1, 1, 1};
    int degree = 3;
    int numPoints = 100;

    std::vector<Point> curvePoints = evaluateRationalNURBSCurve(controlPoints, knotVector, degree, numPoints);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
