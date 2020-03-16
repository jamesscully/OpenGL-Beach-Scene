//
// Created by yames on 3/16/20.
//

#ifndef G53GRA_FRAMEWORK_LIGHT_H
#define G53GRA_FRAMEWORK_LIGHT_H


#include <Interface/DisplayableObject.h>

class Light : public DisplayableObject {

public:
    Light(int light_id);

    // void setAmbient (float amb[]);
    // void setDiffuse (float dif[]);
    // void setSpecular(float spec[]);
    // void setPosition(float pos[]);

    int light_id = 0;

    float ambient [4] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuse [4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    float conAtten = 0.005f;
    float linAtten = 0.005f;
    float quaAtten = 0.005f;

    ~Light() override;

    void Display() override;
};


#endif //G53GRA_FRAMEWORK_LIGHT_H
