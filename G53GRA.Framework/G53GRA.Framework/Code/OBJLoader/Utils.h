//
// Created by yames on 4/5/20.
//

#ifndef G53GRA_FRAMEWORK_UTILS_H
#define G53GRA_FRAMEWORK_UTILS_H



struct vertex {
    float x, y, z;
};

struct vertex2d {
    float x, y;
};

struct face {
    vertex   v1,  v2,  v3;
    vertex2d vt1, vt2, vt3;
    vertex   vn1, vn2, vn3;
};

#endif //G53GRA_FRAMEWORK_UTILS_H
