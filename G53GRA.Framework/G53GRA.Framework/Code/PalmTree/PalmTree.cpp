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

        // as we add more logs, we want i * off_pos so that they "stack"
        float ypos = i * log_offset;
        temp->position(0, ypos , 0);
        temp->size(10);
        logs.push_back(temp);
    }

    int leaf_count = 4;

    // the last log in the vector will be at the top
    Model* parentLog = logs[logs.size() - 1];

    for(int i = 0; i < leaf_count; i++) {
        Model* temp;
        temp = new Model("palm_leaf.obj", "palm_leaf.bmp", false);

        // we want the leaves to be positioned with the top of the tree; parent them
        temp->parent = parentLog;
        temp->size(20);

        leaves.push_back(temp);
    }

}

PalmTree::~PalmTree() {

}

void PalmTree::Display() {
    for(auto x : logs) {
        x->Display();
    }

    for(auto x : leaves) {
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
        x->setOffsetPos(movement, 0, movement);

        speed += dampening;
    }



    for(auto leaf : leaves) {
        float newrot = sin(elapsed * speed) * delta;
        float* leafpos = leaf->position();
        leaf->setOffsetPos(0, 15, 0);
        leaf->setOffsetRot(newrot, 1, 0, 0);
    }



}

