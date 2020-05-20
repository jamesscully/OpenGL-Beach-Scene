//
// Created by yames on 3/16/20.
//

#include "Light.h"
#include "OnscreenText.h"

Light::~Light() = default;

Light::Light(int light_id) : DisplayableObject() {

    // GL_LIGHTx macro is just an integer
    this->light_id = light_id;

    int yRoot = 50;

    // allocate our UI text, with refs to relavent data
    txtLin = new OnscreenText(20, yRoot + 25, "Linear Atten: ", &linAtten);
    txtCon = new OnscreenText(20, yRoot + 50, "Constant Atten: ", &conAtten);
    txtQua = new OnscreenText(20, yRoot + 75, "Quadratic Atten: ", &quaAtten);

}

void Light::Display() {

    glEnable(GL_LIGHTING);

    // set our relavent emission parameters
    glLightfv(light_id, GL_AMBIENT, ambient);
    glLightfv(light_id, GL_DIFFUSE, diffuse);
    glLightfv(light_id, GL_SPECULAR, specular);
    glLightfv(light_id, GL_POSITION, pos);

    // light falloff parameters
    glLightf(light_id, GL_CONSTANT_ATTENUATION, conAtten);
    glLightf(light_id, GL_LINEAR_ATTENUATION, linAtten);
    glLightf(light_id, GL_QUADRATIC_ATTENUATION, quaAtten);

    glFlush();

    glEnable(light_id);

    // render UI text
    txtLin->render();
    txtQua->render();
    txtCon->render();
}

void Light::setColor(float r, float g, float b) {
    float max = 1.5f;

    // too high of a colour set will make it blindly bright
    if(r > max) r = max; if(g > max) g = max; if(b > max) b = max;

    ambient[0]  = r, ambient[1]  = g, ambient[2]  = b;
    diffuse[0]  = r, diffuse[1]  = g, diffuse[2]  = b;
    specular[0] = r, specular[1] = g, specular[2] = b;
}

void Light::HandleKey(unsigned char key, int state, int x, int y) {
    switch (key) {
        case 'j': linAtten -= 0.005; break;
        case 'k': linAtten += 0.005; break;

        case 'n': conAtten -= 0.005; break;
        case 'm': conAtten += 0.005; break;

        case 'h': quaAtten -= 0.0005; break;
        case 'l': quaAtten += 0.0005; break;

        case 'x':
            conAtten = 0.005f; linAtten = 0.005f; quaAtten = 0.005f;
            break;
    }

    if (linAtten < 0) linAtten = 0.0005;
    if (conAtten < 0) conAtten = 0.0005;
    if (quaAtten < 0) quaAtten = 0.0005;
}

