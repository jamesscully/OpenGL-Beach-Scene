//
// Created by yames on 5/17/20.
//

#ifndef G53GRA_FRAMEWORK_SUN_H
#define G53GRA_FRAMEWORK_SUN_H

#include <Interface/DisplayableObject.h>
#include <Interface/Animation.h>
#include <OnscreenText.h>

class Sun : public DisplayableObject, public Animation {
public:
    Sun(int light_id);
    ~Sun() = default;
    void Display() override;
    void Update(const double &deltaTime) override;
    void HandleKey(unsigned char key, int state, int x, int y);

    float radius = 800;
    float speed = 1;
    bool inverted = false;

    bool hidden = false;

private:

    int light_id;

    float ambient [4] = {1.0f, 0.25f, 0.0f, 1.0f};
    float diffuse [4] = {1.0f, 0.25f, 0.0f, 1.0f};
    float specular[4] = {1.0f, 0.25f, 0.0f, 1.0f};

    float conAtten = 0.005f;
    float linAtten = 0.3f;
    float quaAtten = 0.000005f;



    float* origin[3] = {0, 0, 0};



    OnscreenText * txtCon, * txtLin, * txtQua;

};


#endif //G53GRA_FRAMEWORK_SUN_H
