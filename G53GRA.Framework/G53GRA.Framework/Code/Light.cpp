//
// Created by yames on 3/16/20.
//

#include "Light.h"

Light::~Light() = default;

Light::Light(int light_id) : DisplayableObject() {
    this->light_id = light_id;
}

void Light::Display() {
    glEnable(GL_LIGHTING);
    glLightfv(light_id, GL_AMBIENT, ambient);
    glLightfv(light_id, GL_DIFFUSE, diffuse);
    glLightfv(light_id, GL_SPECULAR, specular);
    glLightfv(light_id, GL_POSITION, pos);

    glLightf(light_id, GL_CONSTANT_ATTENUATION, conAtten);
    glLightf(light_id, GL_LINEAR_ATTENUATION, linAtten);
    glLightf(light_id, GL_QUADRATIC_ATTENUATION, quaAtten);
    
    glEnable(light_id);
    
    glDisable(GL_LIGHTING);
}
