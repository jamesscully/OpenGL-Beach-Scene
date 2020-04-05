//
// Created by yames on 4/4/20.
//

#include "Island.h"



void drawIslandQ() {
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glVertex3f(20, 0, 0);

    glColor3f(1, 0, 0);

    glVertex3f(0, 0, 20);
    glVertex3f(0, 0, 40);
    glVertex3f(40, 0, 0);
    glVertex3f(0, 0, 20);

    glColor3f(0, 0, 1);



    glEnd();

}


void Island::Display() {
    drawIslandQ();
}

Island::~Island() = default;

Island::Island()  {

}


