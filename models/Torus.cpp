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

void drawTorus(GLfloat innerRadius, GLfloat outerRadius, GLint sides, GLint rings) {
    GLint i, j;
    GLfloat theta, phi;
    GLfloat x, y, z;

    for (i = 0; i < sides; i++) {
        theta = i * 2.0 * M_PI / sides;
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= rings; j++) {
            phi = j * 2.0 * M_PI / rings;

            x = (outerRadius + innerRadius * cos(theta)) * cos(phi);
            y = (outerRadius + innerRadius * cos(theta)) * sin(phi);
            z = innerRadius * sin(theta);

            glNormal3f(x, y, z);
            glVertex3f(x, y, z);

            x = (outerRadius + innerRadius * cos(theta + 2.0 * M_PI / sides)) * cos(phi);
            y = (outerRadius + innerRadius * cos(theta + 2.0 * M_PI / sides)) * sin(phi);
            z = innerRadius * sin(theta + 2.0 * M_PI / sides);

            glNormal3f(x, y, z);
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
    drawTorus(0.5, 1.0, 50, 50);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Torus");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
