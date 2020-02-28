//
// Created by yames on 2/19/20.
//

#include "Octahedron.h"
#include "OctFace.h"

Octahedron::Octahedron(float height, int subdivide) {
    // bottom half of sphere
    OctFace f1(180, height, false, subdivide);
    OctFace f2(90, height, false, subdivide);
    OctFace f3(180, height, false, subdivide);
    OctFace f4(270, height, false, subdivide);

    // top half of sphere
    OctFace f5(0, height, true, subdivide);
    OctFace f6(90, height, true, subdivide);
    OctFace f7(180, height, true, subdivide);
    OctFace f8(270, height, true, subdivide);
}


