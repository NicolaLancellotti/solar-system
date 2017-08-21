#include <stdio.h>
#include "glutCrossPlatform.h"
#include "preferences.h"
#include "solarSystemScene.h"
#include "Sphere.hpp"

int main(int argc, char *argv[]) 
{
  //______________________________________________________________________________
  //          GLUT
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow(WINDOW_TITLE);
  
  //______________________________________________________________________________
  //          OpenGL
  
  glClearColor(0, 0, 0, 1);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  
  //______________________________________________________________________________
  //          Other init
  
  Sphere::init();
  
  //______________________________________________________________________________
  //            Start
  
  loadSolarSystemScene();
  glutMainLoop();
  return 0;
}
