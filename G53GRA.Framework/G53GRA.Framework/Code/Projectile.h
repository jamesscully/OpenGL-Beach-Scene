//
// Created by yames on 5/20/20.
//

#ifndef G53GRA_FRAMEWORK_PROJECTILE_H
#define G53GRA_FRAMEWORK_PROJECTILE_H


#include <Utility/Camera.h>
#include <Interface/DisplayableObject.h>
#include <Interface/Animation.h>

class Projectile : public DisplayableObject, public Animation {

public:
    Projectile(Camera* c);
    ~Projectile() = default;

    float speed = 10;
    float timeToLive = 5;

private:
    Camera* camera;

    // set in constructor; defines where we started, and what direction
    float start_pos[3] = {0, 0, 0};
    float start_dir[3] = {0, 0, 0};
public:
    void Update(const double &deltaTime) override;

    void Display() override;


};


#endif //G53GRA_FRAMEWORK_PROJECTILE_H
