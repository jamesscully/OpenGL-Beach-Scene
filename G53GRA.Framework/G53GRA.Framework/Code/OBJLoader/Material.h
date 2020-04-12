//
// Created by yames on 4/9/20.
//

#ifndef G53GRA_FRAMEWORK_MATERIAL_H
#define G53GRA_FRAMEWORK_MATERIAL_H


#include <string>

class Material {
public:
    Material(const char* path);
    ~Material();


    std::string name;

    // Ka, Kd, Ks respectively
    float ambient[3], diffuse[3], specular[3];

    // used to weight specular colour
    float specular_exponent = -1;

    // d or 'Tr' in .mtl file
    float transparency;

    // applies the gl commands
    void apply();
};


#endif //G53GRA_FRAMEWORK_MATERIAL_H
