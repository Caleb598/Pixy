#include <iostream>
#include <vector>

struct Point {
    float x;
    float y;
    float z;
};

Point evaluateBezierCurve(const std::vector<Point>& controlPoints, float t) {
    int n = controlPoints.size() - 1;

    // Calculate binomial coefficient
    auto binomialCoeff = [](int n, int k) -> int {
        int res = 1;
        for (int i = 0; i < k; ++i) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    };

    Point result{0.0f, 0.0f, 0.0f};
    for (int i = 0; i <= n; ++i) {
        float blend = binomialCoeff(n, i) * std::pow(1 - t, n - i) * std::pow(t, i);
        result.x += controlPoints[i].x * blend;
        result.y += controlPoints[i].y * blend;
        result.z += controlPoints[i].z * blend;
    }

    return result;
}

std::vector<Point> generateBezierControlPointCurve(const std::vector<Point>& controlPoints, int numPoints) {
    std::vector<Point> curvePoints;

    for (int i = 0; i <= numPoints; ++i) {
        float t = static_cast<float>(i) / numPoints;
        Point point = evaluateBezierCurve(controlPoints, t);
        curvePoints.push_back(point);
    }

    return curvePoints;
}

int main() {
    std::vector<Point> controlPoints = {{0, 0, 0}, {1, 1, 0}, {2, -1, 0}, {3, 0, 0}};
    int numPoints = 100;

    std::vector<Point> curvePoints = generateBezierControlPointCurve(controlPoints, numPoints);
    for (const auto& point : curvePoints) {
        std::cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << std::endl;
    }

    return 0;
}
