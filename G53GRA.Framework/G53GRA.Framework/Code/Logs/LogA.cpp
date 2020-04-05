//
// Created by yames on 4/4/20.
//

#include "LogA.h"

void LogA::Display() {
    glBegin(GL_LINE_LOOP);

    glColor3f(1, 0, 1);
    glVertex3f(0.000000, 0.008070 ,-1.000000);
    glVertex3f(0.125312, 1.788039 ,-0.967411);
    glVertex3f(0.866025, 0.008070 ,-0.500000);
    glVertex3f(0.919840, 1.864264 ,-0.364986);
    glVertex3f(0.866025, 0.008070, 0.500000);
    glVertex3f(0.794528, 2.084295, 0.602425);
    glVertex3f(-0.000000, 0.008070, 1.000000);
    glVertex3f(-0.125312, 2.228101, 0.967411);
    glVertex3f(-0.866025, 0.008070, 0.500000);
    glVertex3f(-0.919840, 2.151875, 0.364986);
    glVertex3f(-0.866025, 0.008070 ,-0.500000);
    glVertex3f(-0.794528, 1.931845 ,-0.602425);
    glEnd();

}

LogA::LogA() {

}

LogA::~LogA() {

}
