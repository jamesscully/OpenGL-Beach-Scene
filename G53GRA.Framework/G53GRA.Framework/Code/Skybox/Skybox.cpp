//
// Created by yames on 4/4/20.
//

#include <GL/glut.h>
#include <OBJLoader/Model.h>
#include "Skybox.h"

Model* sbox;

Skybox::Skybox() {
    sbox = new Model("skydome", "skybox_side_full", false);
}

void Skybox::Display() {
    sbox->position(pos[0],pos[1],pos[2]);
    sbox->size(scale[0],scale[1],scale[2]);

    // we don't want the skybox to be shaded
    sbox->setLighting(false);

    sbox->Display();
}

void Skybox::Update(const double &deltaTime) {
    static float deltaY = 0;

    // allows start point back/forward
    float y_offset = -1;

    // if we've hit max, loop around texture image
    if(deltaY + y_offset >= 1)
        deltaY = 0;

    // function has same built-in loop
    sbox->setOffsetUV(0, deltaY + y_offset);

    // increment static variable
    deltaY += 0.0004;
}
