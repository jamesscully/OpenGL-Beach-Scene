//
// Created by yames on 5/20/20.
//

#include "DockBase.h"
#include "OminousMonkey.h"
#include <OBJLoader/Model.h>
Model* dock_base, *dock_box;
OminousMonkey * monkey;

std::vector<Model*> planks;

DockBase::DockBase() {
    dock_base = new Model("dock_base", "", false); {
        dock_base->position(0, 25, -100);
        dock_base->size(10);
    }

    for(int i = 0; i < plank_count; i++) {
        // space between each plank
        int offset = -25;

        Model* plank = new Model("planks", "plank", false);

        // parent the plank to the base, then apply Z offset from here
        plank->parent = dock_base;
        plank->position(0, 0, (i * offset));

        plank->size(15, 10, 10);

        // make the planks 'twist' and also flip UV map for variety
        if(i % 2) {
            plank->orientation(0, 185, 0);
        }

        planks.push_back(plank);
    }

    dock_box = new Model("dock_box", "crate", false); {
        dock_box->position(30, 50, -275);

        dock_box->orientation(0, 250, 0);
        dock_box->size(7.5);
    }

//    monkey = new Model("monkey", "monkey", false); {
//        // we want the monkey to sit ontop of the box; parent it
//        monkey->parent = dock_box;
//        monkey->position(0, 30, 0);
//        monkey->orientation(0, 250, 40);
//        monkey->size(12.5);
//    }

    monkey = new OminousMonkey();
    monkey->model->parent = dock_box;
    monkey->position(0, 30, 0);
    monkey->orientation(0, 250, 40);
    monkey->size(12.5);
}

void DockBase::Display() {
    dock_box->Display();
    dock_base->Display();
    monkey->Display();

    for(auto x : planks) {
        x->Display();
    }
}

void DockBase::Update(const double &deltaTime) {

}
