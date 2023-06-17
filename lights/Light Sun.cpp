#include <GL/glut.h>  // include the GLUT library

void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // clear the color buffer

   // set up the sunlight
   GLfloat sun_direction[] = { 0.0f, -1.0f, 0.0f, 0.0f };  // direction of the sunlight
   GLfloat sun_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };       // color of the sunlight

   glEnable(GL_LIGHTING);    // enable lighting
   glEnable(GL_LIGHT0);      // enable light 0
   glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);  // set sunlight direction
   glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_color);      // set sunlight color

   // draw your 3D scene here

   glFlush();   // flush the rendering pipeline
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                      // initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set up the display mode
   glutInitWindowSize(800, 600);                // set up the window size
   glutCreateWindow("Sunlight");                // create the window
   glutDisplayFunc(display);                    // register the display callback function
   glutMainLoop();                              // enter the main loop

   return 0;
}
