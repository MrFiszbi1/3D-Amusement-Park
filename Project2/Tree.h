#ifndef _TREE_H_
#define _TREE_H_

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "TargaImage.h"
#include "OBJLoader.h"

struct Vertex {
    float coords[3];
};
struct Triangle {
    GLuint verts[3];
};
struct Mesh {
    struct Vertex vertices[8];
    struct Triangle triangles[12];
};

class Tree {
private:
    GLubyte trunk_list;   // The display list that does all the work.
    GLubyte branch_list;

    GLuint  texture_obj;    // The object for the Building texture.
    bool    initialized;    // Whether or not we have been initialised.
    OBJLoader object;
    OBJLoader object2;

    Mesh mesh;
    unsigned int   textureId;

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Tree(void) { trunk_list = 0, branch_list = 0,  initialized = false; };
    // Destructor. Frees the display lists and texture object.
    ~Tree(void);
    // Initializer. Creates the display list.
    bool    Initialize(void);
    // Does the drawing.
    void    Draw(void);
    bool ResizeImage(TargaImage* image);
    void LoadTexture(const char* filename);
};

#endif
