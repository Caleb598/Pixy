#include <GL/glut.h>  // include the GLUT library

void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // clear the color buffer

   // set up the light point
   GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };  // position of the light
   GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };     // color of the light

   glEnable(GL_LIGHTING);    // enable lighting
   glEnable(GL_LIGHT0);      // enable light 0
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);    // set light position
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);        // set light color

   // draw the light point
   glPushMatrix();
   glTranslatef(0.0f, 0.0f, -5.0f);  // translate to the desired position
   glutSolidSphere(0.1f, 20, 20);   // draw a sphere as the light point
   glPopMatrix();

   glFlush();   // flush the rendering pipeline
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                      // initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set up the display mode
   glutInitWindowSize(800, 600);                // set up the window size
   glutCreateWindow("Light Point");             // create the window
   glutDisplayFunc(display);                    // register the display callback function
   glutMainLoop();                              // enter the main loop

   return 0;
}
