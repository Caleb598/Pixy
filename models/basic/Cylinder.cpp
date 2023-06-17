#include <GL/glut.h>
#include <cmath>

const int screenWidth = 640;
const int screenHeight = 480;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void drawCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
    GLint i, j;
    GLfloat theta, phi;
    GLfloat x, y, z;

    for (i = 0; i < slices; i++) {
        theta = i * 2.0 * M_PI / slices;
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= stacks; j++) {
            phi = j * height / stacks;

            x = radius * cos(theta);
            y = radius * sin(theta);
            z = phi;

            glNormal3f(x, y, 0.0);
            glVertex3f(x, y, z);

            x = radius * cos(theta);
            y = radius * sin(theta);
            z = phi + height / stacks;

            glNormal3f(x, y, 0.0);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    drawCylinder(1.0, 2.0, 50, 50);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Cylinder");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
