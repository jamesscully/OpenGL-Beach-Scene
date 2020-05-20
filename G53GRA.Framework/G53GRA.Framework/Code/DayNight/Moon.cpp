//
// Created by yames on 5/17/20.
//

#include "Moon.h"

#include "VectorMath.h"

Moon::Moon(int light_id) {
    this->light_id = light_id;

    model = new Model("moon", "", false);

    model->size(15);
    model->setLighting(false);

    printf("Start Pos [%f,%f]\n", pos[0], pos[1]);

}

void Moon::Display() {

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
    glLightf(light_id, GL_SPOT_EXPONENT, 10);

    // light falloff parameters
    glLightf(light_id, GL_CONSTANT_ATTENUATION, conAtten);
    glLightf(light_id, GL_LINEAR_ATTENUATION, linAtten);
    glLightf(light_id, GL_QUADRATIC_ATTENUATION, quaAtten);

    glEnable(light_id);


    model->position(pos[0], pos[1], pos[2]);
    model->orientation(rotation[0], rotation[1], rotation[2]);
    model->Display();

    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);
    {
        glColor3f(255, 0, 0);
        glVertex3f(pos[0] - 50, pos[1], pos[2] + 50);
        glVertex3f(pos[0] - 50, pos[1], pos[2] - 50);
        glVertex3f(pos[0] + 50, pos[1], pos[2] - 50);
        glVertex3f(pos[0] + 50, pos[1], pos[2] + 50);
    }
    glEnd();
}

#include <cmath>
void Moon::Update(const double &deltaTime) {

    // can set to offset start position
    static float elapsed = -2.5;

    elapsed += deltaTime;

    float x_movement = 0 + radius * sin(elapsed * speed);
    float y_movement = 0 + radius * cos(elapsed * speed);

    // used to make sun/moon opposite
    if(inverted) {
        x_movement = -x_movement;
        y_movement = -y_movement;
    }

    this->position(x_movement, y_movement, 0);


    float new_rot[3] = {0, 0, 0};

    // get the angle of the moon from (0,0,0)
    float radians = atan2(pos[1], pos[0]);
    float degrees = radians * (180 / M_PI);
//    printf("ATAN2 of (%f,%f) is: %f radians or %f degrees\n", pos[1], pos[0], radians, degrees);


    // rotate model to face (0,0,0)
    orientation(0, 0, degrees);

    // if we're below Y = 0, don't render
    hidden = pos[1] < 0;
}



