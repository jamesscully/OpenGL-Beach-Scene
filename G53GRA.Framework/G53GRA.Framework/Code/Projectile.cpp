//
// Created by yames on 5/20/20.
//

#include <Utility/VectorMath.h>
#include "Projectile.h"

Projectile::Projectile(Camera *c) {
    c->GetEyePosition(start_pos[0], start_pos[1], start_pos[2]);
    c->GetViewDirection(start_dir[0], start_dir[1], start_dir[2]);

    position(start_pos[0], start_pos[1], start_pos[2]);
}

void Projectile::Update(const double &deltaTime) {
    float* new_position = pos;

    // since dir is -1 to 1, we can add the direction to position for next 'frame'; use scale to speed
    add(new_position, start_dir, speed);



    position(new_position[0], new_position[1], new_position[2]);
}

void Projectile::Display() {
    glDisable(GL_LIGHTING);
    {
        glPushMatrix();
        {
            glTranslatef(pos[0], pos[1], pos[2]);
            glColor3f(255, 0, 0);
            glutSolidSphere(10, 10, 10);
        }
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
}