//
// Created by yames on 4/5/20.
//

#ifndef G53GRA_FRAMEWORK_OCEAN_H
#define G53GRA_FRAMEWORK_OCEAN_H


#include <Interface/DisplayableObject.h>

class Ocean : public DisplayableObject {

    ~Ocean();


    void Display() override;

    GLuint oceanTexture;

public:
    Ocean();
};


#endif //G53GRA_FRAMEWORK_OCEAN_H
