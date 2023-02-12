#ifndef _TICKETBUILDING_H_
#define _TICKETBUILDING_H_

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "TargaImage.h"

class TicketBuilding {
private:
    GLubyte display_list;   // The display list that does all the work.
    GLuint  texture_obj;    // The object for the Building texture.
    bool    initialized;    // Whether or not we have been initialised.
    unsigned int   textureId;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    TicketBuilding(void) { display_list = 0; initialized = false; };
    // Destructor. Frees the display lists and texture object.
    ~TicketBuilding(void);
    // Initializer. Creates the display list.
    bool    Initialize(void);
    // Does the drawing.
    void    Draw(void);
    bool ResizeImage(TargaImage* image);
    void LoadTexture(const char* filename);
};

#endif