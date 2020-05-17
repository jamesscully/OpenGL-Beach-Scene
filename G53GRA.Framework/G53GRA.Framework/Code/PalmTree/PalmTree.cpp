//
// Created by yames on 4/9/20.
//

#include "PalmTree.h"
#include <cmath>
#include <OBJLoader/Model.h>

std::vector<Model*> logs;
std::vector<Model*> leaves;

PalmTree::PalmTree() {
    float logcount = 8;
    float log_offset = 18;

    for(int i = 0; i < logcount; i++) {
        Model* temp;

        // get some variety
        if(i % 2)
             temp = new Model("log_A", "log_A", false);
        else
            temp = new Model("log_B", "log_A", false);

        // as we add more logs, we want i * off_pos so that they "stack"


        float ypos = i * log_offset;

        temp->position(0, ypos , 0);

        temp->size(10);
        logs.push_back(temp);
    }

    int leaf_count = 6;

    // the last log in the vector will be at the top
    Model* parentLog = logs[logs.size() - 1];

    float rotY = 0;
    float rotOff = 45;

    float smallY = 0;

    for(int i = 0; i < leaf_count; i++) {
        Model* temp;
        temp = new Model("palm_leaf", "palm_leaf", false);

        // we want the leaves to be positioned with the top of the tree; parent them
        temp->parent = parentLog;
        temp->setOffsetPos(0, 15 + smallY, 0);
        temp->size(20);

        rotY += rotOff;

        temp->orientation(0, rotY, 0);

        leaves.push_back(temp);
        smallY += 0.25;
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
    double delta = 7.5;
    double base_speed = 1;
    double speed = base_speed;
    float dampening = 0.05;

    // from 1 - end not 0 - 1; getting life-like movement is weird
    for(auto it = logs.begin(); it != logs.end(); ++it) {
        Model* x = *it;

        float movement = sin(elapsed * speed) * delta;

        x->setOffsetPos(movement, 0, 0);

        speed += dampening;
    }


    for(auto leaf : leaves) {

        // leaves will want to update only around the X coordinate; makes them move up and down

        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        float change = sin(elapsed * speed) * delta;
        float * rot = leaf->orientation();

         leaf->orientation(change, rot[1], rot[2]);
    }
}

