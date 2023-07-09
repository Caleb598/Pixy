#include <GL/glut.h>  // include the GLUT library

void display() {
   glClear(GL_COLOR_BUFFER_BIT);  // clear the color buffer

   // set up the area light
   const int lightCount = 4;  // number of point lights
   GLfloat light_positions[lightCount][4] = {
       {-1.0f, 1.0f, 0.0f, 1.0f},   // top-left
       {1.0f, 1.0f, 0.0f, 1.0f},    // top-right
       {-1.0f, -1.0f, 0.0f, 1.0f},  // bottom-left
       {1.0f, -1.0f, 0.0f, 1.0f}    // bottom-right
   };
   GLfloat light_color[] = {1.0f, 1.0f, 1.0f, 1.0f};  // color of the area light

   glEnable(GL_LIGHTING);  // enable lighting
   for (int i = 0; i < lightCount; ++i) {
       glEnable(GL_LIGHT0 + i);                              // enable light i
       glLightfv(GL_LIGHT0 + i, GL_POSITION, light_positions[i]);  // set light position
       glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light_color);     // set light color
   }

   // draw your 3D scene here

   glFlush();   // flush the rendering pipeline
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                      // initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set up the display mode
   glutInitWindowSize(800, 600);                // set up the window size
   glutCreateWindow("Area Light");              // create the window
   glutDisplayFunc(display);                    // register the display callback function
   glutMainLoop();                              // enter the main loop

   return 0;
}
