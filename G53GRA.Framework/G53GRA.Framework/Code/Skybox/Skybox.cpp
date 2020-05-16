//
// Created by yames on 4/4/20.
//

#include <GL/gl.h>
#include <OBJLoader/Model.h>
#include "Skybox.h"

Model* sbox;

Skybox::Skybox() {
    sbox = new Model("skydome.obj", "skybox_side_full.bmp", false);
}


void Skybox::Display() {
    sbox->position(pos[0],pos[1],pos[2]);
    sbox->size(scale[0],scale[1],scale[2]);
    sbox->Display();
}

void Skybox::Update(const double &deltaTime) {

    static float off = 0;

    // if we've hit max, loop around
    if(off >= 1)
        off = 0;

    // function has same built-in loop
    sbox->setOffsetUV(0, off);

    // increment static variable
    off += 0.0005;
}
