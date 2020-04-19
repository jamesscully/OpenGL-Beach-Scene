//
// Created by yames on 4/9/20.
//

#include "PalmTree.h"
#include <cmath>
#include <OBJLoader/Model.h>

std::vector<Model*> logs;

PalmTree::PalmTree() {
    float logcount = 6;
    float log_offset = 18;

    for(int i = 0; i < logcount; i++) {
        Model* temp;

        // get some variety
        if(i % 2)
             temp = new Model("log_A.obj", "log_A.bmp", false);
        else
            temp = new Model("log_B.obj", "log_A.bmp", false);

        // as we add more logs, we want i * offset so that they "stack"
        float ypos = i * log_offset;

        temp->position(0, ypos , 0);

        temp->size(10);

        logs.push_back(temp);
    }
}

PalmTree::~PalmTree() {

}

void PalmTree::Display() {
    for(auto x : logs) {
        x->Display();
    }
}

void PalmTree::Update(const double &deltaTime) {
    static double elapsed = 0;
    elapsed += deltaTime;

    // how many seconds should the anim reset/reverse?
    double end_time = 5;

    // this will create a more life-like look
    // dampening = further up, more swing
    float dampening_decrement = -0.2;
    float dampening = 0.2;

    time_t currentTime = time(0);


    for(auto x : logs) {
        float* lpos = x->position();

        float movement = sin(elapsed) * 2;

        printf("%f\n", movement);

        x->position(lpos[0] += movement, lpos[1], lpos[2]);
    }


}

