#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a point in 3D space
struct Point3D {
    double x, y, z;
};

// Function to create a cube with rounded edges
std::vector<Point3D> createRoundedCube(double size, double radius, int subdivisions) {
    std::vector<Point3D> cube;

    // Calculate the half-size of the cube
    double halfSize = size / 2.0;

    // Create the eight corner vertices of the cube
    cube.push_back({-halfSize, -halfSize, -halfSize});
    cube.push_back({-halfSize, -halfSize, halfSize});
    cube.push_back({-halfSize, halfSize, -halfSize});
    cube.push_back({-halfSize, halfSize, halfSize});
    cube.push_back({halfSize, -halfSize, -halfSize});
    cube.push_back({halfSize, -halfSize, halfSize});
    cube.push_back({halfSize, halfSize, -halfSize});
    cube.push_back({halfSize, halfSize, halfSize});

    // Perform subdivision to round the edges
    for (int i = 0; i < subdivisions; ++i) {
        std::vector<Point3D> temp;

        for (int j = 0; j < cube.size(); j += 4) {
            // Get the four vertices of a subdivision face
            Point3D p1 = cube[j];
            Point3D p2 = cube[j + 1];
            Point3D p3 = cube[j + 2];
            Point3D p4 = cube[j + 3];

            // Calculate the midpoints of the four edges
            Point3D m12 = {(p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0, (p1.z + p2.z) / 2.0};
            Point3D m23 = {(p2.x + p3.x) / 2.0, (p2.y + p3.y) / 2.0, (p2.z + p3.z) / 2.0};
            Point3D m34 = {(p3.x + p4.x) / 2.0, (p3.y + p4.y) / 2.0, (p3.z + p4.z) / 2.0};
            Point3D m41 = {(p4.x + p1.x) / 2.0, (p4.y + p1.y) / 2.0, (p4.z + p1.z) / 2.0};

            // Calculate the new vertices on the edges
            Point3D np12 = {m12.x + radius * (m12.x - (p3.x + p4.x) / 2.0), m12.y + radius * (m12.y - (p3.y + p4.y) / 2.0), m12.z + radius * (m12.z - (p3.z + p4.z) / 2.0)};
            Point3D np23 = {m23.x + radius * (m23.x - (p4.x + p1.x) / 2.0), m23.y + radius * (m23.y - (p4.y + p1.y) / 2.0), m23.z + radius * (m23.z - (p4.z + p1.z) / 2.0)};
            Point3D np34 = {m34.x + radius * (m34.x - (p1.x + p2.x) / 2.0), m34.y + radius * (m34.y - (p1.y + p2.y) / 2.0), m34.z + radius * (m34.z - (p1.z + p2.z) / 2.0)};
            Point3D np41 = {m41.x + radius * (m41.x - (p2.x + p3.x) / 2.0), m41.y + radius * (m41.y - (p2.y + p3.y) / 2.0), m41.z + radius * (m41.z - (p2.z + p3.z) / 2.0)};

            // Add the new vertices to the temporary vector
            temp.push_back(p1);
            temp.push_back(np12);
            temp.push_back(np41);
            temp.push_back(np34);

            temp.push_back(p2);
            temp.push_back(np23);
            temp.push_back(np12);
            temp.push_back(np41);

            temp.push_back(p3);
            temp.push_back(np34);
            temp.push_back(np23);
            temp.push_back(np12);

            temp.push_back(p4);
            temp.push_back(np41);
            temp.push_back(np34);
            temp.push_back(np23);
        }

        // Replace the original cube with the subdivided faces
        cube = temp;
    }

    return cube;
}

int main() {
    double size = 1.0;      // Size of the cube
    double radius = 0.2;    // Radius of the rounded edges
    int subdivisions = 2;   // Number of subdivisions

    std::vector<Point3D> roundedCube = createRoundedCube(size, radius, subdivisions);

    // Print the vertices of the rounded cube
    for (int i = 0; i < roundedCube.size(); ++i) {
        std::cout << "Vertex " << i + 1 << ": (" << roundedCube[i].x << ", "
                  << roundedCube[i].y << ", " << roundedCube[i].z << ")\n";
    }

    return 0;
}
