//
// Created by yames on 4/4/20.
//

#ifndef G53GRA_FRAMEWORK_SKYBOX_H
#define G53GRA_FRAMEWORK_SKYBOX_H

#include <Interface/DisplayableObject.h>
#include <Interface/Animation.h>

class Skybox : public DisplayableObject, public Animation {

public:

    Skybox();
    ~Skybox() = default;
    void Display() override;
    void Update(const double &deltaTime) override;
};


#endif //G53GRA_FRAMEWORK_SKYBOX_H
