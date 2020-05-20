//
// Created by yames on 5/20/20.
//

#include "OminousMonkey.h"

OminousMonkey::OminousMonkey() {
    model = new Model("monkey", "monkey", false);
    light = new Light(GL_LIGHT7);

    light->setColor(0.4, 0.4, 1);
}


void OminousMonkey::Update(const double &deltaTime) {

}

void OminousMonkey::Display() {

    model->position(pos[0], pos[1], pos[2]);
    model->orientation(rotation[0], rotation[1], rotation[2]);
    model->size(scale[0], scale[1], scale[2]);

    model->Display();


    light->position(pos[0], pos[1], pos[2]);

    light->Display();
}

void OminousMonkey::HandleKey(unsigned char key, int state, int x, int y) {

    switch (key) {
        case 'j': light->linAtten -= 0.005; break;
        case 'k': light->linAtten += 0.005; break;

        case 'n': light->conAtten -= 0.005; break;
        case 'm': light->conAtten += 0.005; break;

        case 'h': light->quaAtten -= 0.0005; break;
        case 'l': light->quaAtten += 0.0005; break;

        case 'x':
            light->conAtten = 0.005f; light->linAtten = 0.005f; light->quaAtten = 0.005f;
            break;
    }

    if (light->linAtten < 0) light->linAtten = 0.0005;
    if (light->conAtten < 0) light->conAtten = 0.0005;
    if (light->quaAtten < 0) light->quaAtten = 0.0005;
}

