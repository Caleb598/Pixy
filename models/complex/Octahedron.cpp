#include <iostream>
#include <vector>

// Structure to represent a point in 3D space
struct Point3D {
    double x, y, z;
};

// Function to create an octahedron with given points
std::vector<Point3D> createOctahedron() {
    std::vector<Point3D> octahedron(8);

    // Define the points of the octahedron
    octahedron[0] = {0.0, 0.0, 1.0};    // Vertex 1
    octahedron[1] = {0.0, 0.0, -1.0};   // Vertex 2
    octahedron[2] = {1.0, 0.0, 0.0};    // Vertex 3
    octahedron[3] = {-1.0, 0.0, 0.0};   // Vertex 4
    octahedron[4] = {0.0, 1.0, 0.0};    // Vertex 5
    octahedron[5] = {0.0, -1.0, 0.0};   // Vertex 6

    return octahedron;
}

int main() {
    std::vector<Point3D> octahedron = createOctahedron();

    // Print the vertices of the octahedron
    for (int i = 0; i < octahedron.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << octahedron[i].x << ", "
                  << octahedron[i].y << ", " << octahedron[i].z << ")\n";
    }

    return 0;
}
