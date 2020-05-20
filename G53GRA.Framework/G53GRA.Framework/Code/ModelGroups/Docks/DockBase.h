//
// Created by yames on 5/20/20.
//

#ifndef G53GRA_FRAMEWORK_DOCKBASE_H
#define G53GRA_FRAMEWORK_DOCKBASE_H


#include <Interface/Animation.h>
#include <Interface/DisplayableObject.h>

class DockBase : public DisplayableObject, public Animation {
public:
    DockBase();
    ~DockBase() = default;

    void Display() override;
    void Update(const double &deltaTime) override;


    int plank_count = 10;
};


#endif //G53GRA_FRAMEWORK_DOCKBASE_H
