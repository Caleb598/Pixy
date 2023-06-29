#include <iostream>
#include <unordered_map>

using namespace std;

class InfiniteGrid {
private:
    unordered_map<int, unordered_map<int, int>> grid;

public:
    int getValue(int x, int y) const {
        if (grid.count(x) > 0 && grid.at(x).count(y) > 0) {
            return grid.at(x).at(y);
        }
        return 0; // Default value for undefined cells
    }

    void setValue(int x, int y, int value) {
        grid[x][y] = value;
    }
};

int main() {
    InfiniteGrid grid;

    // Set values at specific coordinates
    grid.setValue(0, 0, 1);
    grid.setValue(2, -1, 5);
    grid.setValue(10, 10, 20);

    // Accessing and printing the grid values
    for (int x = -5; x <= 5; ++x) {
        for (int y = -5; y <= 5; ++y) {
            int value = grid.getValue(x, y);
            cout << "Coordinates: (" << x << ", " << y << "), Value: " << value << endl;
        }
    }

    return 0;
}
