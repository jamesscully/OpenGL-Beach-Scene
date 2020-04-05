//
// Created by yames on 4/4/20.
//

#ifndef G53GRA_FRAMEWORK_LOGA_H
#define G53GRA_FRAMEWORK_LOGA_H


#include <Interface/DisplayableObject.h>

class LogA : public DisplayableObject {
    ~LogA() override;

    void Display() override;

public:
    LogA();
};


#endif //G53GRA_FRAMEWORK_LOGA_H
