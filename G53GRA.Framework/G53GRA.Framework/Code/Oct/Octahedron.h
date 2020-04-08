//
// Created by yames on 2/19/20.
//

#ifndef G53GRA_FRAMEWORK_OCTAHEDRON_H
#define G53GRA_FRAMEWORK_OCTAHEDRON_H

#include "OctFace.h"

class Octahedron {
public:
    Octahedron(float height, int subdivide);
    ~Octahedron() = default;


    OctFace f5, f6, f7, f8;

    void draw();

};


#endif //G53GRA_FRAMEWORK_OCTAHEDRON_H
