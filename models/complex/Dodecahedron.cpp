#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a point in 3D space
struct Point3D {
    double x, y, z;
};

// Function to create a dodecahedron with given points
std::vector<Point3D> createDodecahedron() {
    std::vector<Point3D> dodecahedron(20);

    // Golden ratio
    double phi = (1 + std::sqrt(5.0)) / 2.0;

    // Define the points of the dodecahedron
    dodecahedron[0] = {1.0, 1.0, 1.0};                        // Vertex 1
    dodecahedron[1] = {-1.0, 1.0, 1.0};                       // Vertex 2
    dodecahedron[2] = {-1.0, -1.0, 1.0};                      // Vertex 3
    dodecahedron[3] = {1.0, -1.0, 1.0};                       // Vertex 4
    dodecahedron[4] = {1.0, 1.0, -1.0};                       // Vertex 5
    dodecahedron[5] = {-1.0, 1.0, -1.0};                      // Vertex 6
    dodecahedron[6] = {-1.0, -1.0, -1.0};                     // Vertex 7
    dodecahedron[7] = {1.0, -1.0, -1.0};                      // Vertex 8
    dodecahedron[8] = {0.0, 1.0 / phi, phi};                  // Vertex 9
    dodecahedron[9] = {0.0, -1.0 / phi, phi};                 // Vertex 10
    dodecahedron[10] = {0.0, 1.0 / phi, -phi};                // Vertex 11
    dodecahedron[11] = {0.0, -1.0 / phi, -phi};               // Vertex 12
    dodecahedron[12] = {1.0 / phi, phi, 0.0};                 // Vertex 13
    dodecahedron[13] = {-1.0 / phi, phi, 0.0};                // Vertex 14
    dodecahedron[14] = {1.0 / phi, -phi, 0.0};                // Vertex 15
    dodecahedron[15] = {-1.0 / phi, -phi, 0.0};               // Vertex 16
    dodecahedron[16] = {phi, 0.0, 1.0 / phi};                 // Vertex 17
    dodecahedron[17] = {-phi, 0.0, 1.0 / phi};                // Vertex 18
    dodecahedron[18] = {phi, 0.0, -1.0 / phi};                // Vertex 19
    dodecahedron[19] = {-phi, 0.0, -1.0 / phi};               // Vertex 20

    return dodecahedron;
}

int main() {
    std::vector<Point3D> dodecahedron = createDodecahedron();

    // Print the vertices of the dodecahedron
    for (int i = 0; i < dodecahedron.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << dodecahedron[i].x << ", "
                  << dodecahedron[i].y << ", " << dodecahedron[i].z << ")\n";
    }

    return 0;
}
