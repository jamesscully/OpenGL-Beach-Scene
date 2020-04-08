//
// Created by yames on 2/19/20.
//

#include "Octahedron.h"
#include "OctFace.h"

// ugly, but this way we can keep OctFaces in our object for easily drawing them
Octahedron::Octahedron(float height, int subdivide) :
    f5(0, height, true, subdivide),
    f6(90, height, true, subdivide),
    f7(180, height, true, subdivide),
    f8(270, height, true, subdivide)
{

}

void Octahedron::draw() {
    f5.draw();
    f6.draw();
    f7.draw();
    f8.draw();
}


