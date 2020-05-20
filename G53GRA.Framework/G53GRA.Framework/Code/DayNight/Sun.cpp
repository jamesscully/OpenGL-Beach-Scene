//
// Created by yames on 5/17/20.
//

#include "Sun.h"

Sun::Sun(int light_id) {
    this->light_id = light_id;

    int yRoot = 50;

    txtLin = new OnscreenText(20, yRoot + 25, "Linear Atten: ", &linAtten);
    txtCon = new OnscreenText(20, yRoot + 50, "Constant Atten: ", &conAtten);
    txtQua = new OnscreenText(20, yRoot + 75, "Quadratic Atten: ", &quaAtten);
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
    glLightf(light_id, GL_SPOT_EXPONENT, 10);

    // light falloff parameters
    glLightf(light_id, GL_CONSTANT_ATTENUATION, conAtten);
    glLightf(light_id, GL_LINEAR_ATTENUATION, linAtten);
    glLightf(light_id, GL_QUADRATIC_ATTENUATION, quaAtten);

    // draw sphere to illustrate where spot of light is in screenshots
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

    txtLin->render();
    txtQua->render();
    txtCon->render();
}

#include <cmath>
void Sun::Update(const double &deltaTime) {

    static float elapsed = -2.5;

    elapsed += deltaTime;

    float x_movement = 0 + radius * sin(elapsed * speed);
    float y_movement = 0 + radius * cos(elapsed * speed);

    if(inverted) {
        x_movement = -x_movement;
        y_movement = -y_movement;
    }

    this->position(x_movement, y_movement, 0);

    // if we're below Y = 0, don't render
    hidden = pos[1] < 0;
}

void Sun::HandleKey(unsigned char key, int state, int x, int y) {
    switch (key) {
        case 'j': linAtten -= 0.05; break;
        case 'k': linAtten += 0.05; break;

        case 'n': conAtten -= 0.05; break;
        case 'm': conAtten += 0.05; break;

        case 'h': quaAtten -= 0.05; break;
        case 'l': quaAtten += 0.05; break;

        case 'x':
            conAtten = 0.005f; linAtten = 0.005f; quaAtten = 0.005f;
            break;
    }

    if (linAtten < 0) linAtten = 0.0005;
    if (conAtten < 0) conAtten = 0.0005;
    if (quaAtten < 0) quaAtten = 0.0005;
}


