//
// Created by yames on 4/4/20.
//

#include <stdio.h>
#include <GL/gl.h>
#include "Skybox.h"


GLuint side;
GLuint top;

Skybox::Skybox() {
    side = Scene::GetTexture("/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Textures/skybox_side.bmp");
    top  = Scene::GetTexture("/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Textures/skybox_top.bmp");
}

void Skybox::Display() {
    drawFace(0);
    drawFace(90);
    drawFace(180);
    drawFace(270);
    drawFace(SKYBOX_FLOOR);
    drawFace(SKYBOX_CEILING);
}


void Skybox::drawFace(float rot) {
    float size = this->scale[0];
    float pt = size / 2;

    // whether we're drawing floor or roof
    bool roof = rot == SKYBOX_CEILING;
    bool flor = rot == SKYBOX_FLOOR;


    GLuint texture = side;

    if(roof || flor)
        texture = top;

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    if(roof)
        glRotatef(270, 1, 0, 0);
    else if (flor)
        glRotatef(90, 1, 0, 0);
    else
        glRotatef(rot, 0, 1, 0);


    /* 0 - size / 2
 * x1 - - - - x2        size / 2
 * |   xx      |
 * x3 - - - - x4
*/

    glColor3f(1.0f, 1.0f, 1.0f);

    // we don't want the skybox to be shaded
    glDisable(GL_LIGHTING);


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glBindTexture(GL_TEXTURE_2D, texture);



    static float moveA = 0;
    static float moveB = 1;


    glBegin(GL_QUADS);

    glTexCoord2f(moveA, moveA); glVertex3f(-pt, -pt, pt); // x3
    glTexCoord2f(moveA, moveB); glVertex3f(-pt, pt, pt); // x1
    glTexCoord2f(moveB, moveB); glVertex3f(pt, pt, pt);  // x2
    glTexCoord2f(moveB, moveA); glVertex3f(pt, -pt, pt);

    glEnd();


//    float speed = 0.00005f;
//    moveA = (moveA >= 1) ? 0 : moveA + speed;
    // moveB = (moveB >= 1) ? 0 : moveB + 0.1f;

  //  printf("moveA: %f moveB: %f\n", moveA, moveB);


    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    glPopAttrib();
    glPopMatrix();



}
