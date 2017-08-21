#ifndef Material_cpp
#define Material_cpp

#include <stdio.h>
#include "glutCrossPlatform.h"

class Material {
  
public:
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
  
  void apply();  
};
#endif /* Material_cpp */
