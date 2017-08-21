#include <string>
#include "loadTexture.h"
#include "freeImage.h"
#include "preferences.h"

const static GLenum cube[6] = {
  GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
  GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
  GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
  GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

GLuint loadTexture(char name[])	
{
  char path[20] = RESOURCE_PATH;
  strcat(path, name);
  
  FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(path, 0);
  FIBITMAP *dib = FreeImage_Load(fifmt, path,0);
  dib = FreeImage_ConvertTo24Bits(dib);
  if (dib == nullptr) {
    printf("Texture not loaded");
  }
  BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
  
  GLuint idTexture;
  glGenTextures( 1, &idTexture );
  glBindTexture( GL_TEXTURE_2D, idTexture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  
  glTexImage2D(GL_TEXTURE_2D, 0, 3, 
               FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );
  
  glGenerateMipmap(GL_TEXTURE_2D);
  
  FreeImage_Unload(dib);
  return idTexture;
}


GLuint loadCubeTexture(char texCubeFaces[6][50])
{    
  GLuint idTexture;
  glGenTextures(1, &idTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);
  
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP); 
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  
  for(int i = 0; i < 6; i++){
    char path[100] = RESOURCE_PATH;
    strcat(path, texCubeFaces[i]);
    
    FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(path, 0); 
    FIBITMAP *dib = FreeImage_Load(fifmt, path, 0);
    dib = FreeImage_ConvertTo24Bits(dib);
    if (dib == nullptr) {
      printf("Texture not loaded");
    }
    BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
    
    glTexImage2D(cube[i], 0, 3,
                 FreeImage_GetWidth(dib), FreeImage_GetHeight(dib), 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels );
    
    FreeImage_Unload(dib);
  }
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  
  return idTexture;
}
