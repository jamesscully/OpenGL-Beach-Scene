//
// Created by yames on 5/20/20.
//

#include "OminousMonkey.h"
#include <cmath>

OminousMonkey::OminousMonkey() {
    model = new Model("monkey", "monkey", false);
    light = new Light(GL_LIGHT7);

    light->setColor(0.4, 0.4, 1);
}


void OminousMonkey::Update(const double &deltaTime) {
    static double elapsed = 0;
    elapsed += deltaTime;
    light->linAtten = light->linAtten + sin(elapsed) * 0.005;
}

void OminousMonkey::Display() {

    if(hidden) {
        glDisable(GL_LIGHT7);
        return;
    } else
        glEnable(GL_LIGHT7);


    this->position(pos[0], pos[1], pos[2]);

    model->position(pos[0], pos[1], pos[2]);
    model->orientation(rotation[0], rotation[1], rotation[2]);
    model->size(scale[0], scale[1], scale[2]);
    model->Display();

    light->linAtten = 0.018;
    light->conAtten = 0.005;
    light->quaAtten = 0.009;

    light->position(pos[0], pos[1] + 50, pos[2]);
    light->Display();
}

void OminousMonkey::HandleKey(unsigned char key, int state, int x, int y) {

    // hide this if F is pressed, it can cause performance issues
    if((key == 'f' || key == 'F') && state) {
        hidden = !hidden;
    }
}
