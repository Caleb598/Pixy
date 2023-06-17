#include <iostream>
#include <unordered_map>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point& p) const {
        size_t h1 = hash<int>{}(p.x);
        size_t h2 = hash<int>{}(p.y);
        return h1 ^ h2;
    }
};

int main() {
    unordered_map<Point, int, PointHash> grid;

    // Set values at specific coordinates
    grid[Point(0, 0)] = 1;
    grid[Point(2, -1)] = 5;
    grid[Point(10, 10)] = 20;

    // Accessing and printing the grid values
    for (const auto& pair : grid) {
        const Point& point = pair.first;
        int value = pair.second;
        cout << "Coordinates: (" << point.x << ", " << point.y << "), Value: " << value << endl;
    }

    return 0;
}
