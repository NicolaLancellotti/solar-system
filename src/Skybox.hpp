#ifndef Skybox_cpp
#define Skybox_cpp

#include <stdio.h>
#include "glutCrossPlatform.h"

class Skybox {
  GLuint _texture;
  GLfloat _centre[3];
  
public:
  
  Skybox(char texCubeFaces[6][50]);
  
  void render();
  
  GLfloat* centre()
  {
    return _centre;
  }
  
};

#endif /* Skybox_cpp */
