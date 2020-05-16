//
// Created by yames on 4/9/20.
//

#ifndef G53GRA_FRAMEWORK_MATERIAL_H
#define G53GRA_FRAMEWORK_MATERIAL_H


#include <string>

class Material {
public:
    Material(std::string path);
    ~Material();


    std::string name;

    float ambient[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse[4]  = {1.0f, 1.0f, 1.0f, 1.0f};

    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    // we want it to be shiny
    float shiny[1] = {0.0f};

//    // Ka, Kd, Ks respectively
//    float ambient[3], diffuse[3], specular[3];
//
//    // used to weight specular colour
//    float specular_exponent = -1;
//
//    // d or 'Tr' in .mtl file
//    float transparency;
//
//    // applies the gl commands
//    void apply();

private:
    void extractAmbient(std::string line);
    void extractDiffuse(std::string line);
    void extractSpecular(std::string line);
    void extractTransparency(std::string line, bool invert);

};


#endif //G53GRA_FRAMEWORK_MATERIAL_H
