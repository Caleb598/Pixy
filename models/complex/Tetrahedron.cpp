#include <iostream>
#include <vector>

// Structure to represent a point in 3D space
struct Point3D {
    double x, y, z;
};

// Function to create a tetrahedron with given points
std::vector<Point3D> createTetrahedron() {
    std::vector<Point3D> tetrahedron(4);

    // Define the points of the tetrahedron
    tetrahedron[0] = {0.0, 0.0, 0.0};   // Vertex 1
    tetrahedron[1] = {1.0, 0.0, 0.0};   // Vertex 2
    tetrahedron[2] = {0.0, 1.0, 0.0};   // Vertex 3
    tetrahedron[3] = {0.0, 0.0, 1.0};   // Vertex 4

    return tetrahedron;
}

int main() {
    std::vector<Point3D> tetrahedron = createTetrahedron();

    // Print the vertices of the tetrahedron
    for (int i = 0; i < tetrahedron.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << tetrahedron[i].x << ", "
                  << tetrahedron[i].y << ", " << tetrahedron[i].z << ")\n";
    }

    return 0;
}
