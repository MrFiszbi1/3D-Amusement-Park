#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_
#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "TargaImage.h"

using namespace std;
struct vec3 {
    float x;
    float y;
    float z;
};

struct vec2 {
    float s;
    float t;
};

class OBJLoader {   
public:
    OBJLoader(void) { };
    ~OBJLoader(void);
    bool loadOBJ(const char* name);

    vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    vector< vec3 > vertices;
    vector< vec2 > uvs;
    vector< vec3 > normals;
    vector< vec3 > temp_vertices;
    vector< vec2 > temp_uvs;
    vector< vec3 > temp_normals;
};

#endif