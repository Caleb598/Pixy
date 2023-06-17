#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a point in 3D space
struct Point3D {
    double x, y, z;
};

// Function to create an icosahedron with given points
std::vector<Point3D> createIcosahedron() {
    std::vector<Point3D> icosahedron(12);

    // Golden ratio
    double phi = (1 + std::sqrt(5.0)) / 2.0;

    // Define the points of the icosahedron
    icosahedron[0] = {0.0, 1.0, phi};       // Vertex 1
    icosahedron[1] = {0.0, -1.0, phi};      // Vertex 2
    icosahedron[2] = {0.0, 1.0, -phi};      // Vertex 3
    icosahedron[3] = {0.0, -1.0, -phi};     // Vertex 4
    icosahedron[4] = {1.0, phi, 0.0};       // Vertex 5
    icosahedron[5] = {-1.0, phi, 0.0};      // Vertex 6
    icosahedron[6] = {1.0, -phi, 0.0};      // Vertex 7
    icosahedron[7] = {-1.0, -phi, 0.0};     // Vertex 8
    icosahedron[8] = {phi, 0.0, 1.0};       // Vertex 9
    icosahedron[9] = {-phi, 0.0, 1.0};      // Vertex 10
    icosahedron[10] = {phi, 0.0, -1.0};     // Vertex 11
    icosahedron[11] = {-phi, 0.0, -1.0};    // Vertex 12

    return icosahedron;
}

int main() {
    std::vector<Point3D> icosahedron = createIcosahedron();

    // Print the vertices of the icosahedron
    for (int i = 0; i < icosahedron.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << icosahedron[i].x << ", "
                  << icosahedron[i].y << ", " << icosahedron[i].z << ")\n";
    }

    return 0;
}
