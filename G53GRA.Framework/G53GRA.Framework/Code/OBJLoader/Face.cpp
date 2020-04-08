//
// Created by yames on 4/8/20.
//

#include <GL/gl.h>
#include "Face.h"

void Face::draw() {
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
}
