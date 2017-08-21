#include "Camera.h"

Camera::Camera()
{
  //    Volume of view
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, ASPECT_RATIO_WIDTH / ASPECT_RATIO_HEIGHT, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  _movement = {false, false, false, false, false, false};
}

void Camera::reshape(int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Camera::update(GLfloat timeInterval)
{
  if(_movement.moveForward) {
    _pos = _pos + (SPEED_FORWARD_BACKWARD * timeInterval) * _dir;
    _at = _pos + _dir;
  }
  
  if(_movement.moveBackward) {
    _pos = _pos - (SPEED_FORWARD_BACKWARD * timeInterval) * _dir;
    _at = _pos + _dir;
  }
  
  if(_movement.rotateLeft) {
    _dir = rotate_vector(_dir, cml::vector3f(0.0, 1.0, 0.0), (SPEED_ANGLE_ROTATE * timeInterval));
    _at = _pos + _dir;
    _side = cross(_dir, _up);
    _side.normalize();
  }
  
  if(_movement.rotateRight) {
    _dir = rotate_vector(_dir, cml::vector3f(0.0, 1.0, 0.0), - (SPEED_ANGLE_ROTATE * timeInterval));
    _at = _pos + _dir;
    _side = cross(_dir, _up);
    _side.normalize();
  }
  
  if(_movement.moveLeft) {
    _pos = _pos - (SPEED_LEFT_RIGHT * timeInterval) * _side;
    _at = _pos + _dir;
  }
  
  if(_movement.moveRight) {
    _pos = _pos + (SPEED_LEFT_RIGHT * timeInterval) * _side;
    _at = _pos + _dir;
  }
}

void Camera::place()
{
  gluLookAt(_pos[0], _pos[1], _pos[2],
            _at[0], _at[1], _at[2],
            _up[0], _up[1], _up[2]);
}
