#include <cmath>
#include "Planet.h"
#include "loadTexture.h"
#include "preferences.h"
#include "Sphere.hpp"

GLfloat Planet::orbitalPeriodSpeed = 1.0;
GLfloat Planet::rotationPeriodSpeed = 1.0;

Planet::Planet(GLfloat rotationPeriod,
               GLfloat orbitalPeriod,
               GLfloat orbitalDistance,
               GLfloat radius, char textureName[]) :
_rotationPeriod(rotationPeriod),
_orbitalPeriod(orbitalPeriod),
_orbitalDistance(orbitalDistance),
_radius(radius) 
{    
  _texture = loadTexture(textureName);
  
  //    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  //    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  //    GLfloat planes[] = { 0.5f, 0.0f, 0.5f, 0.5f };
  //    GLfloat planet[] = { 0.0f, 0.5f, 0.0f, 0.5f };
  //    glTexGenfv(GL_S, GL_OBJECT_PLANE, planes);
  //    glTexGenfv(GL_T, GL_OBJECT_PLANE, planet);
  
  _material.ambient[0] = 0.1;
  _material.ambient[1] = 0.1;
  _material.ambient[2] = 0.1;
  _material.ambient[3] = 1;
  
  _material.diffuse[0] = _material.specular[0] = 1;
  _material.diffuse[1] = _material.specular[1] = 1;
  _material.diffuse[2] = _material.specular[2] = 1;
  _material.diffuse[3] = _material.specular[3] = 1;
  
  _material.shininess = 50;
}

void Planet::update(GLfloat timeInterval)
{     
  for (Planet &moon : _moons) {
    moon.update(timeInterval);
  }
  
  _angleRotation += 360.0 * timeInterval / _rotationPeriod * rotationPeriodSpeed;
  _angleOrbital += 360.0 * timeInterval / _orbitalPeriod * orbitalPeriodSpeed;
  
  if (_angleOrbital > 360) {
    _angleOrbital -= 360;
  }
  
  if (_angleRotation > 360) {
    _angleRotation -= 360;
  }  
}

void Planet::render()
{
  //        Render orbit
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glColor3f(0.5, 0, 1);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; ++i) {
    GLfloat x = cos(i * M_PI / 180) * _orbitalDistance;
    GLfloat z = sin(i * M_PI / 180) * _orbitalDistance;
    glVertex3f(x, 0, z);
  }
  glEnd();
  glPopMatrix();
  
  
  //        Render planet and moons
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  //    glEnable(GL_TEXTURE_GEN_S);
  //    glEnable(GL_TEXTURE_GEN_T);
  
  glPushMatrix();
  glRotatef(_angleOrbital, 0, 1, 0); 
  glTranslatef(_orbitalDistance, 0, 0);
  
  glPushMatrix();        
  glRotated(_angleRotation, 0, 1, 0);
  glRotated(-90, 1, 0, 0); // fix for texture
  glScaled(_radius, _radius, _radius);
  glBindTexture(GL_TEXTURE_2D, _texture); 
  _material.apply();
  glColor4f(1, 1, 1, 1);
  Sphere::render();
  
  glPopMatrix();
  
  for (Planet &moon : _moons) {
    moon.render();
  }
  glPopMatrix();   
  
  //    glDisable(GL_TEXTURE_GEN_S);
  //    glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_2D);
}

void Planet::addMoon(Planet moon)
{
  _moons.push_back(moon);
}




