//
// Created by yames on 4/4/20.
//

#ifndef G53GRA_FRAMEWORK_SKYBOX_H
#define G53GRA_FRAMEWORK_SKYBOX_H

#include <Interface/DisplayableObject.h>

#define SKYBOX_SIDE 1
#define SKYBOX_CEILING 5
#define SKYBOX_FLOOR 10

class Skybox : public DisplayableObject {

public:

    Skybox();
    ~Skybox() = default;

    void Display() override;

    void drawFace(float rot = 0);


};


#endif //G53GRA_FRAMEWORK_SKYBOX_H
