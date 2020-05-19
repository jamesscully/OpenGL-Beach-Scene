//
// Created by yames on 5/18/20.
//

#ifndef G53GRA_FRAMEWORK_MOON_H
#define G53GRA_FRAMEWORK_MOON_H


#include <OnscreenText.h>
#include <Interface/DisplayableObject.h>
#include <Interface/Animation.h>
#include <OBJLoader/Model.h>

class Moon : public DisplayableObject, public Animation {
public:
    Moon(int light_id);
    ~Moon() = default;
    void Display() override;
    void Update(const double &deltaTime) override;
    void HandleKey(unsigned char key, int state, int x, int y);

    float radius = 100;

    float speed = 1;

    bool inverted = false;


private:

    int light_id;

    Model* model;

    float ambient [4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse [4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    float conAtten = 0.005f;
    float linAtten = 0.3f;
    float quaAtten = 0.000005f;


    float* origin[3] = {0, 0, 0};

    OnscreenText * txtCon, * txtLin, * txtQua;

};


#endif //G53GRA_FRAMEWORK_MOON_H
