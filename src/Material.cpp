#include "Material.hpp"

void Material::apply()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
