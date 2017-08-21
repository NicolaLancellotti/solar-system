#include "Skybox.hpp"
#include "glutCrossPlatform.h"
#include "loadTexture.h"

//    3_______2
//   /|     /|
//  / |    / |
// 7------|6 |
// | 0|___|__|1
// | /    | /
// |/     |/
// 4--------5

static const GLfloat vertices[] = {
  -1, -1, -1,
  1, -1, -1,
  1,  1, -1,
  -1,  1, -1,
  -1, -1,  1,
  1, -1,  1,
  1,  1,  1,
  -1,  1,  1
};

static const GLubyte frontFace[]  = {0, 1, 2, 3};
static const GLubyte backFace[]   = {4, 7, 6, 5};
static const GLubyte leftFace[]   = {1, 5, 6, 2};
static const GLubyte rightFace[]  = {4, 0, 3, 7};
static const GLubyte topFace[]    = {3, 2, 6, 7};
static const GLubyte bottomFace[] = {4, 5, 1, 0};

Skybox::Skybox(char texCubeFaces[6][50])
{
  _texture = loadCubeTexture(texCubeFaces);
}

void Skybox::render()
{
  glPushMatrix();
  glTranslated(_centre[0], _centre[1], _centre[2]);
  glScaled(500, 500, 500);
  
  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_CUBE_MAP);
  
  glTexCoordPointer(3, GL_FLOAT, 0, vertices);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColor3f(1, 1, 1);
  
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontFace);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backFace);
  
  glPopMatrix();
  
  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_CUBE_MAP);
}
