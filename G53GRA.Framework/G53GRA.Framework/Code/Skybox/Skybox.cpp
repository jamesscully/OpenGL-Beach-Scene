//
// Created by yames on 4/4/20.
//

#include "Skybox.h"


GLuint side;

Skybox::Skybox() {
    side = Scene::GetTexture("/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Textures/skybox_side.bmp");
}

void Skybox::Display() {
    drawFace(SKYBOX_SIDE);
    drawFace(SKYBOX_SIDE);
    drawFace(SKYBOX_SIDE);
    drawFace(SKYBOX_SIDE);
    drawFace(SKYBOX_FLOOR);
    drawFace(SKYBOX_CEILING);
}


void Skybox::drawFace(float rot) {
    float size = this->scale[0];
    float pt = size / 2;

    static float sides = 0;

    if(rot == SKYBOX_SIDE)
        sides++;

    float rotation = sides * 90;

    bool bside = rot == SKYBOX_SIDE;
    bool roof = rot == SKYBOX_CEILING;
    bool flor = rot == SKYBOX_FLOOR;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    if(roof)
        glRotatef(270, 1, 0, 0);
    else if (flor)
        glRotatef(90, 1, 0, 0);
    else
        glRotatef(rotation, 0, 1, 0);


    /* 0 - size / 2
 * x1 - - - - x2        size / 2
 * |   xx      |
 * x3 - - - - x4
*/

    glColor3f(1.0f, 1.0f, 1.0f);

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glBindTexture(GL_TEXTURE_2D, side);

    static int move = 0;

    glBegin(GL_QUADS);

    glTexCoord2d(0, 0); glVertex3f(-pt, -pt, pt); // x3
    glTexCoord2d(0, 1); glVertex3f(-pt, pt, pt); // x1
    glTexCoord2d(1, 1); glVertex3f(pt, pt, pt);  // x2
    glTexCoord2d(1, 0); glVertex3f(pt, -pt, pt);

    glEnd();

    move++;

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
    glPopMatrix();



}
