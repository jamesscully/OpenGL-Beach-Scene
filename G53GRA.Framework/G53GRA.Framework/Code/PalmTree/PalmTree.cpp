//
// Created by yames on 4/9/20.
//

#include "PalmTree.h"
#include <cmath>
#include <OBJLoader/Model.h>

std::vector<Model*> logs;
std::vector<Model*> leaves;

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

    // how far we want it to move in one direction
    float delta = 7.5;
    float base_speed = 1;

    float speed = base_speed;

    float dampening = 0.1;

    // from 1 - end not 0 - 1; getting life-like movement is weird
    for(auto it = ++logs.begin(); it != logs.end(); ++it) {
        Model* x = *it;

        float movement = sin(elapsed * speed) * delta;
        x->setOffset(movement, 0, movement);

        speed += dampening;
    }



}

