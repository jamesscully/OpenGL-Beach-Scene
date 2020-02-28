//
// Created by yames on 2/19/20.
//

#ifndef G53GRA_FRAMEWORK_OCTFACE_H
#define G53GRA_FRAMEWORK_OCTFACE_H


class OctFace {

public:
    OctFace(float rot, float height, bool flip, int subdivLevel);
    ~OctFace();

private:
	void subdivide(float a[], float b[], float c[], int level);

};


#endif //G53GRA_FRAMEWORK_OCTFACE_H
