#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265358979323846;

void drawCapsule(float radius, float height, int segments) {
    const float halfHeight = height / 2.0;
    const float segmentAngle = 2.0 * PI / segments;

    // Draw the upper hemisphere
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, halfHeight + radius);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * segmentAngle;
        glVertex3f(radius * std::cos(angle), radius * std::sin(angle), halfHeight);
    }
    glEnd();

    // Draw the lower hemisphere
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, -halfHeight - radius);
    for (int i = segments; i >= 0; --i) {
        float angle = i * segmentAngle;
        glVertex3f(radius * std::cos(angle), radius * std::sin(angle), -halfHeight);
    }
    glEnd();

    // Draw the cylindrical body
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * segmentAngle;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);

        glNormal3f(x, y, 0.0);
        glVertex3f(x, y, halfHeight);
        glVertex3f(x, y, -halfHeight);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(45.0, 1.0, 1.0, 0.0);

    glColor3f(0.7, 0.7, 0.7);
    drawCapsule(1.0, 2.0, 16);

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Capsule Shape");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
    return 0;
}
