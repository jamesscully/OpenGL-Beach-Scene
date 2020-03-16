//
// Created by yames on 3/4/20.
//

#ifndef G53GRA_FRAMEWORK_WALL_H
#define G53GRA_FRAMEWORK_WALL_H


#include <Interface/DisplayableObject.h>

class Wall : public DisplayableObject {



public:
    Wall();
    ~Wall();

    float ambient[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    float diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    float SPEC_SHADE = 0.5f;
    float specular[4] = { SPEC_SHADE, SPEC_SHADE, SPEC_SHADE, 1.0f};

    // we want it to be shiny
    float shiny[1] = {0.0f};

    void Display();


};


#endif //G53GRA_FRAMEWORK_WALL_H
