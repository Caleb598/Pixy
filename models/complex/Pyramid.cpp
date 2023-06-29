#include <GL/glut.h>

void drawPyramid() {
    // Vertices of the pyramid
    GLfloat vertices[] = {
        0.0, 1.0, 0.0,  // Top vertex
        -1.0, -1.0, 1.0,  // Front left vertex
        1.0, -1.0, 1.0,  // Front right vertex
        1.0, -1.0, -1.0,  // Back right vertex
        -1.0, -1.0, -1.0  // Back left vertex
    };

    // Indices of the pyramid faces
    GLint indices[] = {
        0, 1, 2,  // Front face
        0, 2, 3,  // Right face
        0, 3, 4,  // Back face
        0, 4, 1,  // Left face
        1, 2, 4,  // Bottom face 1
        2, 3, 4   // Bottom face 2
    };

    // Set color
    glColor3f(0.7, 0.7, 0.7);

    // Draw the pyramid
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 18; i += 3) {
        glVertex3fv(&vertices[3 * indices[i]]);
        glVertex3fv(&vertices[3 * indices[i + 1]]);
        glVertex3fv(&vertices[3 * indices[i + 2]]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(45.0, 1.0, 1.0, 0.0);

    drawPyramid();

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
    glutCreateWindow("Pyramid Shape");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}
