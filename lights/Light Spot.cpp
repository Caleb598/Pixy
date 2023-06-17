#include <GL/glut.h>  // include the GLUT library

void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // clear the color buffer

   // set up the spot light
   GLfloat spot_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // position of the spotlight
   GLfloat spot_direction[] = { 0.0f, 0.0f, -1.0f };     // direction of the spotlight
   GLfloat spot_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // color of the spotlight

   glEnable(GL_LIGHTING);    // enable lighting
   glEnable(GL_LIGHT0);      // enable light 0
   glLightfv(GL_LIGHT0, GL_POSITION, spot_position);    // set spotlight position
   glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);  // set spotlight direction
   glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);           // set spotlight cutoff angle
   glLightfv(GL_LIGHT0, GL_DIFFUSE, spot_color);        // set spotlight color

   // draw your 3D scene here

   glFlush();   // flush the rendering pipeline
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                      // initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set up the display mode
   glutInitWindowSize(800, 600);                // set up the window size
   glutCreateWindow("Spotlight");               // create the window
   glutDisplayFunc(display);                    // register the display callback function
   glutMainLoop();                              // enter the main loop

   return 0;
}
