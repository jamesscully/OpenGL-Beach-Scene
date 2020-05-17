//
// Created by yames on 4/4/20.
//

#include <GL/gl.h>
#include <OBJLoader/Model.h>
#include "Skybox.h"

Model* sbox;

Skybox::Skybox() {
    sbox = new Model("skydome", "skybox_side_full", false);
}

void Skybox::Display() {
    sbox->position(pos[0],pos[1],pos[2]);
    sbox->size(scale[0],scale[1],scale[2]);
    sbox->setLighting(false);

    sbox->Display();
}

void Skybox::Update(const double &deltaTime) {

    static float deltaY = 0;

    // so we can offset the 'time' e.g. day time start
    float static offsetY = 0.7;

    // if we've hit max, loop around
    if(deltaY >= 1)
        deltaY = 0;

    // function has same built-in loop
    sbox->setOffsetUV(0, deltaY + offsetY);

    // increment static variable
    deltaY += 0.0005;
}
