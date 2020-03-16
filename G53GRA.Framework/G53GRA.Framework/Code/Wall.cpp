//
// Created by yames on 3/4/20.
//

#include "Wall.h"

Wall::Wall() = default;
Wall::~Wall() = default;

void Wall::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_LIGHTING);

    glScalef(scale[0], scale[1], scale[2]);

    // set our materials properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiny);

    float wallsize = 2.0f;

    // how many times we want to sub-divide
    float SUB_SCALE = 100.0f;

    float sample = 1.0f / SUB_SCALE;

    /*
     *  * - - - - - - - - - - *  (x + sample, y + sample)
     *  |                     |
     *  |                     |
     *  |                     |
     *  * - - - - - - - - - - *
     *  (x,y)                (x + sample, y)
     *
     */

    for(GLfloat x = -wallsize; x < wallsize; x += sample) {
        for(GLfloat y = -wallsize; y < wallsize; y += sample) {
            glBegin(GL_TRIANGLES);

            float colour_scale = 0.4f;
            glColor3f(colour_scale, colour_scale, colour_scale);

            glVertex3f(x, y, 0);
            glVertex3f(x + sample, y, 0);
            glVertex3f(x + sample, y + sample, 0);

            glVertex3f(x, y, 0);
            glVertex3f(x + sample, y + sample, 0);
            glVertex3f(x, y + sample, 0);

            glEnd();

        }
    }

    glPopAttrib();
    glPopMatrix();
}
