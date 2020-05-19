//
// Created by yames on 4/5/20.
//

#include "Ocean.h"

Ocean::Ocean() {

}

Ocean::~Ocean() = default;


void Ocean::Display() {
    // must implement waves!

    float size = scale[0];

    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);
        glColor4f(0.52f, 0.81f, 0.98, 0.5);
        glVertex3d(-size, 0, size);
        glVertex3d(size, 0, size);
        glVertex3d(size, 0, -size);
        glVertex3d(-size, 0, -size);
    glEnd();

    glDisable(GL_LIGHTING);

}
