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

std::vector<Point> generateBSplineControlPointCurve(const std::vector<Point>& controlPoints, const std::vector<float>& knotVector, int degree, int numPoints) {
    std::vector<Point> curvePoints;

    int n = controlPoints.size() - 1;

    for (int i = degree; i <= n; ++i) {
        for (int j = 0; j <= numPoints; ++j) {
            float t = static_cast<float>(j) / numPoints;

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            for (int k = 0; k <= degree; ++k) {
                float basis = calculateBasis(knotVector, degree, i - degree + k, t);
                x += controlPoints[i - degree + k].x * basis;
                y += controlPoints[i - degree + k].y * basis;
                z += controlPoints[i - degree + k].z * basis;
            }

            curvePoints.push_back({x, y, z});
        }
    }

    return curvePoints;
}

int main() {
    std::vector<Point> controlPoints = {{0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0}};
    std::vector<float> knotVector = {0, 0, 0, 1, 1, 1};  // Uniform knot vector
    int degree = 2;
    int numPoints = 100;

    std::vector<Point> curvePoints = generateBSplineControlPointCurve(controlPoints, knotVector, degree, numPoints);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
