//
// Created by yames on 3/16/20.
//

#ifndef G53GRA_FRAMEWORK_LIGHT_H
#define G53GRA_FRAMEWORK_LIGHT_H


#include <Interface/DisplayableObject.h>
#include "OnscreenText.h"

class Light : public DisplayableObject {

public:
    Light(int light_id);

    int light_id = 0;

    float ambient [4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float diffuse [4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    float conAtten = 0.005f;
    float linAtten = 0.005f;
    float quaAtten = 0.005f;

    ~Light() override;

    void Display() override;

    OnscreenText * txtCon, * txtLin, * txtQua;

    void setColor(float r, float g, float b);
    void HandleKey(unsigned char key, int state, int x, int y);
};


#endif //G53GRA_FRAMEWORK_LIGHT_H
