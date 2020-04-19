//
// Created by yames on 4/9/20.
//

#ifndef G53GRA_FRAMEWORK_PALMTREE_H
#define G53GRA_FRAMEWORK_PALMTREE_H


#include <Interface/DisplayableObject.h>
#include <Interface/Animation.h>

class PalmTree : public DisplayableObject, public Animation {

public:
    PalmTree();
    ~PalmTree() override;

    void Display() override;

    void Update(const double &deltaTime) override;
};


#endif //G53GRA_FRAMEWORK_PALMTREE_H
