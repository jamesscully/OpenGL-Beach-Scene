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

    float radius = 100;

    float speed = 1;

    bool inverted = false;

    bool hidden = false;


private:
    int light_id;

    Model* model;

    float ambient [4] = {0.7f, 1.0f, 0.7f, 1.0f};
    float diffuse [4] = {0.7f, 1.0f, 0.7f, 1.0f};
    float specular[4] = {0.7f, 1.0f, 0.7f, 1.0f};

    float conAtten = 0.005f;
    float linAtten = 0.1f;
    float quaAtten = 0.0005f;
};


#endif //G53GRA_FRAMEWORK_MOON_H
