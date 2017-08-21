#ifndef __glutCrossPlatform__
#define __glutCrossPlatform__

#ifdef WIN32
    #include <windows.h>
#endif

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif


#endif /* defined(__glutCrossPlatform__) */
