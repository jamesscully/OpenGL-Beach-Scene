//
// Created by yames on 4/8/20.
//

#ifndef G53GRA_FRAMEWORK_FACE_H
#define G53GRA_FRAMEWORK_FACE_H


#include "Utils.h"

class Face {

public:

    Face(GLuint * uv);
    ~Face() = default;

    int id;

    GLuint * texture;

    // we'll triangulate faces when exporting from blender
    // example format: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ..
    vertex v1, v2,  v3;
    uv_coord vt1, vt2, vt3;
    vertex vn1, vn2, vn3;

    void draw(float* pos, float* rot, float* scale);
};


#endif //G53GRA_FRAMEWORK_FACE_H
