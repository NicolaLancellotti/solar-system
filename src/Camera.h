#ifndef Camera_cpp
#define Camera_cpp

#include <stdio.h>
#include <cml/cml.h>
#include "glutCrossPlatform.h"
#include "preferences.h"

struct movement_t {
  bool moveLeft;
  bool moveRight;
  bool moveForward;
  bool moveBackward;
  bool rotateLeft;
  bool rotateRight;
};

class Camera {
  cml::vector3f _pos = {0.0, 1.0, 30};		
  cml::vector3f _at = {0.0, 1.0, 0.0};	
  cml::vector3f _up = {0.0, 1.0, 0.0};		
  
  cml::vector3f _dir = {0.0, 0.0, -0.1};	
  cml::vector3f _side = {1.0, 0.0, 0.0};	
  movement_t _movement;
  
public:
  
  Camera();
  
  void reshape(int width, int height);
  
  void update(GLfloat timeInterval);
  
  void place();
  
  void getPos(GLfloat pos[])
  {
    pos[0] = _pos[0];
    pos[1] = _pos[1];
    pos[2] = _pos[2];
  }
  
  movement_t& movement()
  {
    return _movement;
  }
  
};

#endif /* Camera_cpp */
