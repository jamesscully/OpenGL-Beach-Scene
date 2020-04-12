//
// Created by yames on 4/9/20.
//

#ifndef G53GRA_FRAMEWORK_PALMTREE_H
#define G53GRA_FRAMEWORK_PALMTREE_H


#include <Interface/DisplayableObject.h>

class PalmTree : public DisplayableObject {

public:
    PalmTree();
    ~PalmTree() override;

    void Display() override;
};


#endif //G53GRA_FRAMEWORK_PALMTREE_H
