#include <GL/glut.h>  // include the GLUT library

void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // clear the color buffer

   // set up the ambient light
   GLfloat ambient_color[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // color of the ambient light

   glEnable(GL_LIGHTING);    // enable lighting
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);  // set ambient light color

   // draw your 3D scene here

   glFlush();   // flush the rendering pipeline
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                      // initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set up the display mode
   glutInitWindowSize(800, 600);                // set up the window size
   glutCreateWindow("Ambient Light");           // create the window
   glutDisplayFunc(display);                    // register the display callback function
   glutMainLoop();                              // enter the main loop

   return 0;
}
