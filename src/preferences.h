#ifndef __preferences__
#define __preferences__

#include <stdio.h>

//______________________________________________________________________________
//      Aspect ratio: 16:9

#define ASPECT_RATIO_WIDTH  16.0
#define ASPECT_RATIO_HEIGHT  9.0

//______________________________________________________________________________
//      Window

#define WINDOW_WIDTH  ASPECT_RATIO_WIDTH * 70
#define WINDOW_HEIGHT ASPECT_RATIO_HEIGHT * 70
#define WINDOW_TITLE "Solar System"
#define WINDOW_POSITION_X 0
#define WINDOW_POSITION_Y 0

//______________________________________________________________________________
//      Camera

#define SPEED_LEFT_RIGHT 5
#define SPEED_FORWARD_BACKWARD 70
#define SPEED_ANGLE_ROTATE 1

//______________________________________________________________________________
//      Other

#define RESOURCE_PATH "assets/"

//______________________________________________________________________________
//      Planets

// ORBITAL_DISTANCE in Km
// ORBITAL_PERIOD in days
// ROTATION_PERIOD in days
// RADIUS in Km

#define MERCURY_ORBITAL_PERIOD 87.9
#define MERCURY_ORBITAL_DISTANCE 46001272.0
#define MERCURY_ROTATION_PERIOD 58.6
#define MERCURY_RADIUS 4879 / 2.0

#define VENUS_ORBITAL_PERIOD 224.7
#define VENUS_ORBITAL_DISTANCE 107476002.0
#define VENUS_ROTATION_PERIOD -243.0
#define VENUS_RADIUS 12103 / 2.0

#define EARTH_ORBITAL_PERIOD 365.2
#define EARTH_ORBITAL_DISTANCE 147098074.0
#define EARTH_ROTATION_PERIOD 0.99
#define EARTH_RADIUS 12756 / 2.0

#define MOON_ORBITAL_PERIOD 27.3
#define MOON_ORBITAL_DISTANCE 363300.0
#define MOON_ROTATION_PERIOD MOON_ORBITAL_PERIOD
#define MOON_RADIUS 3476 / 2.0

#define MARS_ORBITAL_PERIOD 686.9
#define MARS_ORBITAL_DISTANCE 206644545.0
#define MARS_ROTATION_PERIOD 1.0
#define MARS_RADIUS 6804 / 2.0

#define JUPITER_ORBITAL_PERIOD 4333.28
#define JUPITER_ORBITAL_DISTANCE 740742598.0
#define JUPITER_ROTATION_PERIOD 0.41
#define JUPITER_RADIUS 142984 / 2.0

#endif /* defined(__preferences__) */
