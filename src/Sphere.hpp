#ifndef Sphere_cpp
#define Sphere_cpp

#include <stdio.h>
#include "glutCrossPlatform.h"

class Sphere {
  static int _displayList;
  
public:
  static void init();
  
  static void render()
  {
    glCallList(Sphere::_displayList);
  }
  
};

#endif /* Sphere_cpp */
