#include "solarSystemScene.h"
#include "glutCrossPlatform.h"
#include "preferences.h"
#include "Planet.h"
#include "Camera.h"
#include "Skybox.hpp"
#include "Light.h"
#include "Sphere.hpp"
#include "loadTexture.h"

// _____________________________________________________________________________
#pragma mark - Declarations

static void initSkybox();
static void initLight();
static void initPlanets();

static void renderSun();
static GLfloat getTimeInterval(GLfloat second);

// Callbacks
static void dispalyCallback(void);
static void reshapeCallBack(int width, int height);
static void idleCallBack(void);
static void keyboardCallback(unsigned char key, int x, int y);
static void keyboardUpCallback(unsigned char key, int x, int y);
static void specialCallback(int key, int x, int y);

//______________________________________________________________________________
#pragma mark - Variables

static Camera *camera;
static Light *light;
static Skybox *skybox;
static std::vector<Planet> *planets;

//______________________________________________________________________________
#pragma mark - Callbacks

void dispalyCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  camera->place();
  
  light->apply();
  skybox->render();
  
  renderSun();
  for (Planet &planet : *planets) {
    planet.render();
  }
  
  glutSwapBuffers();
}

void reshapeCallBack(int width, int height)
{
  camera->reshape(width, height);
}

void idleCallBack(void)
{
  GLfloat timeInterval = getTimeInterval(0.0);
  if (timeInterval == 0) {
    return;
  }
  camera->update(timeInterval);
  
  // Set the skybox center with the position of the camera
  camera->getPos(skybox->centre());
  
  for (Planet &planet : *planets) {
    planet.update(timeInterval);
  }
  glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y)
{
  switch(key) {
    case 'w':
      camera->movement().moveForward = true;
      break;
    case 's':
      camera->movement().moveBackward = true;
      break;
    case 'd':
      camera->movement().rotateRight = true;
      break;
    case 'a':
      camera->movement().rotateLeft = true;
      break;
    case 'x':
      camera->movement().moveRight = true;
      break;
    case 'z':
      camera->movement().moveLeft = true;
      break;
    case 'q':
      exit(0);
    case 'f':
      static bool fullScreen = false;
      if (fullScreen) {
        glutPositionWindow(WINDOW_POSITION_X, WINDOW_POSITION_Y);
        glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
      } else {
        glutFullScreen();
      }
      fullScreen = !fullScreen;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
  switch(key) {
    case 'w':
      camera->movement().moveForward = false;
      break;
    case 's':
      camera->movement().moveBackward = false;
      break;
    case 'd':
      camera->movement().rotateRight = false;
      break;
    case 'a':
      camera->movement().rotateLeft = false;
      break;
    case 'x':
      camera->movement().moveRight = false;
      break;
    case 'z':
      camera->movement().moveLeft = false;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void specialCallback(int key, int x, int y)
{
  GLfloat orbitalPeriodSpeed = Planet::orbitalPeriodSpeed;
  switch(key) {
    case GLUT_KEY_UP:
      Planet::orbitalPeriodSpeed = orbitalPeriodSpeed == 0 ? 1 : orbitalPeriodSpeed + 5;
      break;
    case GLUT_KEY_DOWN:
      Planet::orbitalPeriodSpeed = orbitalPeriodSpeed <= 1 ? 0 : orbitalPeriodSpeed - 5;
      break;
  }
}

//______________________________________________________________________________
#pragma mark - Load scene

void loadSolarSystemScene()
{
  camera = new Camera();
  
  initSkybox();
  initPlanets();
  initLight();
  
  //    Callbacks
  glutDisplayFunc(dispalyCallback);
  glutReshapeFunc(reshapeCallBack);
  glutIdleFunc(idleCallBack);
  glutSpecialFunc(specialCallback);
  glutKeyboardFunc(keyboardCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  
}

void changeScene(void(loadScene)(void)) 
{
  delete camera;
  delete light;
  delete skybox;
  delete planets;
  
  glutReshapeFunc(nullptr);
  glutIdleFunc(nullptr);
  glutSpecialFunc(nullptr);
  glutSpecialUpFunc(nullptr);
  glutKeyboardFunc(nullptr);
  glutKeyboardUpFunc(nullptr);
  loadScene();
  glutPostRedisplay();
}

//______________________________________________________________________________
#pragma mark - Init 

void initSkybox()
{
  char texCubeFaces[6][50] = {
    "xPositive.png",
    "xNegative.png",
    "yPositive.png",
    "yNegative.png",
    "zPositive.png",
    "zNegative.png",
  };
  skybox = new Skybox(texCubeFaces);
}

void initPlanets()
{
  planets = new std::vector<Planet>;
  
  GLfloat factorRadius = 1e4;
  GLfloat factorOrbitalDistance = 1e7;
  
  char textureMercury[20] = "mercurymap.jpg";
  Planet mercury(MERCURY_ROTATION_PERIOD,
                 MERCURY_ORBITAL_PERIOD,
                 MERCURY_ORBITAL_DISTANCE / factorOrbitalDistance,
                 MERCURY_RADIUS / factorRadius,
                 textureMercury);
  planets->push_back(mercury);
  
  char textureVenus[20] = "venusmap.jpg";
  Planet venus(VENUS_ROTATION_PERIOD,
               VENUS_ORBITAL_PERIOD,
               VENUS_ORBITAL_DISTANCE / factorOrbitalDistance,
               VENUS_RADIUS / factorRadius,
               textureVenus);
  planets->push_back(venus);
  
  char textureEarth[20] = "earthmap.jpg";
  Planet earth(EARTH_ROTATION_PERIOD,
               EARTH_ORBITAL_PERIOD,
               EARTH_ORBITAL_DISTANCE / factorOrbitalDistance,
               EARTH_RADIUS / factorRadius,
               textureEarth);
  char textureMoon[20] = "moonmap.jpg";
  Planet moon(MOON_ROTATION_PERIOD,
              MOON_ORBITAL_PERIOD,
              MOON_ORBITAL_DISTANCE / factorOrbitalDistance + 1.5,
              MOON_RADIUS / factorRadius,
              textureMoon);
  earth.addMoon(moon);
  planets->push_back(earth);
  
  char textureMars[20] = "marsmap.jpg";
  Planet mars(MARS_ROTATION_PERIOD,
              MARS_ORBITAL_PERIOD,
              MARS_ORBITAL_DISTANCE / factorOrbitalDistance,
              MARS_RADIUS / factorRadius,
              textureMars);
  planets->push_back(mars);
  
  
  char textureJupiter[20] = "jupitermap.jpg";
  Planet jupiter(JUPITER_ROTATION_PERIOD,
                 JUPITER_ORBITAL_PERIOD,
                 JUPITER_ORBITAL_DISTANCE / factorOrbitalDistance,
                 JUPITER_RADIUS / factorRadius,
                 textureJupiter);
  planets->push_back(jupiter);
}

void initLight()
{   
  light = new Light();
  
  light->position[0] = 0;
  light->position[1] = 0;
  light->position[2] = 0;
  light->position[3] = 1;
  
  light->ambient[0] = light->diffuse[0] = light->specular[0] =  1;
  light->ambient[1] = light->diffuse[1] = light->specular[1] =  1;
  light->ambient[2] = light->diffuse[2] = light->specular[2] =  1;
  light->ambient[3] = light->diffuse[3] = light->specular[3] =  1;
}

//______________________________________________________________________________
#pragma mark - Other

/*
 Return the number of seconds passed since the last call of this function,
 if the number if greater then "second", 0 otherwise.
 */
GLfloat getTimeInterval(GLfloat seconds)
{
  static GLfloat lastTime = 0;
  GLfloat now = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  GLfloat timeInterval = now - lastTime;
  if (timeInterval < seconds) {
    return 0;
  }
  lastTime = now;
  return timeInterval;
}

void renderSun()
{
  static char textureSun[] = "sunmap.jpg";
  static GLuint _texture = loadTexture(textureSun);
  
  glDisable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  GLfloat  radius = 695800.0 / 1e6 ;
  glScaled(radius, radius, radius);
  glColor3f( 1.0f, 1.0f, 1.0f );
  glBindTexture(GL_TEXTURE_2D, _texture);
  Sphere::render();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}
