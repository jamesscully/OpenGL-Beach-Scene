//
// Created by yames on 4/4/20.
//

#ifndef G53GRA_FRAMEWORK_ISLAND_H
#define G53GRA_FRAMEWORK_ISLAND_H


#include <Interface/DisplayableObject.h>

class Island : public DisplayableObject {

public:
    Island();
    ~Island() override;


    void Display() override;
};


#endif //G53GRA_FRAMEWORK_ISLAND_H
