//
// Created by yames on 5/17/20.
//

#include "Sun.h"

Sun::Sun(int light_id) {
    this->light_id = light_id;
}

void Sun::Display() {

    if(hidden) {
        glDisable(light_id);
        return;
    }
    glEnable(GL_LIGHTING);

    // set our relavent emission parameters
    glLightfv(light_id, GL_AMBIENT, ambient);
    glLightfv(light_id, GL_DIFFUSE, diffuse);
    glLightfv(light_id, GL_SPECULAR, specular);
    glLightfv(light_id, GL_POSITION, pos);

    float spot_dir[] = {0.0, -1.0, 0.0};
    glLightfv(light_id, GL_SPOT_DIRECTION, spot_dir);
    glLightf(light_id, GL_SPOT_CUTOFF, 90.0);
    glLightf(light_id, GL_SPOT_EXPONENT, 0);

    // light falloff parameters
    glLightf(light_id, GL_CONSTANT_ATTENUATION, conAtten);
    glLightf(light_id, GL_LINEAR_ATTENUATION, linAtten);
    glLightf(light_id, GL_QUADRATIC_ATTENUATION, quaAtten);

    // draw sphere as the sun
    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        glColor3f(0.9, 0.5, 0.1);
        glTranslatef(pos[0], pos[1], pos[2]);
        glutSolidSphere(10, 16, 16 );
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);


    glFlush();

    glEnable(light_id);
}

#include <cmath>
void Sun::Update(const double &deltaTime) {

    static float elapsed = -5;

    elapsed += deltaTime;

    float x_movement = radius * sin(elapsed * speed);
    float y_movement = radius * cos(elapsed * speed);

    if(inverted) {
        x_movement = -x_movement;
        y_movement = -y_movement;
    }

    this->position(x_movement, y_movement, 0);

    // if we're below Y = 0, don't render
    hidden = pos[1] < 0;
}


