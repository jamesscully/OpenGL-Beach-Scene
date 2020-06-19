//
// Created by yames on 5/20/20.
//

#ifndef G53GRA_FRAMEWORK_OMINOUSMONKEY_H
#define G53GRA_FRAMEWORK_OMINOUSMONKEY_H

#include <Interface/Animation.h>
#include <Interface/DisplayableObject.h>
#include <OBJLoader/Model.h>
#include <Light.h>

class OminousMonkey : public Animation, public DisplayableObject, public Input {
public:
    OminousMonkey();
    ~OminousMonkey() = default;

    void Display() override;

    void Update(const double &deltaTime) override;
    void HandleKey(unsigned char key, int state, int x, int y) override;


    Model* model;

private:
    Light* light;

};


#endif //G53GRA_FRAMEWORK_OMINOUSMONKEY_H
