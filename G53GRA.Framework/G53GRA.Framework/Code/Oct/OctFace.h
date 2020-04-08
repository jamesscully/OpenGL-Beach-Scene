//
// Created by yames on 2/19/20.
//

#ifndef G53GRA_FRAMEWORK_OCTFACE_H
#define G53GRA_FRAMEWORK_OCTFACE_H


struct vertice {
    float x;
    float y;
    float z;
};

class OctFace {

public:
    OctFace(float rot, float height, bool flip, int subdivLevel);
    ~OctFace();

    void draw();


private:
	void subdivide(float a[], float b[], float c[], int level);

    int faces = 1;
    int vcount = 0;

    float height = 0;

    int rot = 0;

    vertice* verts;

    float* midpoint(const float a[], const float b[]);
};


#endif //G53GRA_FRAMEWORK_OCTFACE_H
