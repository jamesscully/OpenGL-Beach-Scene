//
// Created by yames on 5/20/20.
//

#include <Utility/VectorMath.h>
#include "Projectile.h"

Projectile::Projectile(Camera *c) {
    c->GetEyePosition(start_pos[0], start_pos[1], start_pos[2]);

    // get the direction we're looking in
    c->GetViewDirection(start_dir[0], start_dir[1], start_dir[2]);

    // move to camera's position
    position(start_pos[0], start_pos[1], start_pos[2]);
}


void Projectile::Update(const double &deltaTime) {

    timeElapsed += deltaTime;

    // hide this projectile if our object is too old
    if(timeElapsed > timeToLive) {
        hidden = true;
        return;
    }

    float* new_position = pos;

    // since dir is -1 to 1, we can add the direction to position for next 'frame'; use scale to speed
    add(new_position, start_dir, speed);

    // add pseudo-gravity to object; slowly make Y dir go down per frame
    start_dir[1] -= deltaTime * 0.5;

    position(new_position[0], new_position[1], new_position[2]);
}

void Projectile::Display() {

    // if we're hidden, don't waste resources drawing the model
    if(hidden)
        return;

    // draw our projectile model
    model->position(pos[0], pos[1], pos[2]);
    model->Display();
}

void Projectile::setModel(Model *m) {
    model = m;

    // orientate the projectile's randomly
    float r = (float) (rand()) / (float) (RAND_MAX  * 90);
    model->orientation(r, r, -r);

    model->size(10);
}
