#ifndef _BOAT_H_
#define _BOAT_H_

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "TargaImage.h"
#include "OBJLoader.h"

class Boat {
private:
    GLdouble boat_list;   // The display list that does all the work.
    GLdouble stand_list;

    bool    initialized;    // Whether or not we have been initialised.
    OBJLoader object;
    OBJLoader object2;
    unsigned int   textureId;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Boat(void) { textureId = 0, initialized = false; };
    // Destructor. Frees the display lists and texture object.
    ~Boat(void);
    // Initializer. Creates the display list.
    bool    Initialize(void);
    // Does the drawing.
    void    Draw(void);
    bool ResizeImage(TargaImage* image);
    void LoadTexture(const char* filename);
};

#endif

