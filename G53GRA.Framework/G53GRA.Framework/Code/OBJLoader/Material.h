//
// Created by yames on 4/9/20.
//

#ifndef G53GRA_FRAMEWORK_MATERIAL_H
#define G53GRA_FRAMEWORK_MATERIAL_H


#include <string>

class Material {
public:
    Material();
    Material(std::string path);
    ~Material();


    std::string name = "default";

    // default material values; white non shiny
    float ambient[4]  = {1.0f, 1.0f, 1.0f, 1.0f}; // Ka
    float diffuse[4]  = {1.0f, 1.0f, 1.0f, 1.0f}; // Kd
    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Ks

    float shiny[1] = {1.0f};

    float transparency = 1.0f; // d or Tr

    float emission[4] = {0, 0, 0, 1.0f};

    void print() {
        printf("Material %s properties: \n", name.c_str());
        printf("Ambient : %f %f %f\n", ambient[0], ambient[1], ambient[2]);
        printf("Diffuse : %f %f %f\n", diffuse[0], diffuse[1], diffuse[2]);
        printf("Specular: %f %f %f\n", specular[0], specular[1], specular[2]);
        printf("Shiny   : %f\n", shiny[0]);
        printf("Transparency: %f\n", transparency);
    }

private:
    void extractAmbient(std::string line);
    void extractDiffuse(std::string line);
    void extractSpecular(std::string line);
    void extractTransparency(std::string line, bool invert);
    void extractEmission(std::string line);
    void extractShininess(std::string line);

};


#endif //G53GRA_FRAMEWORK_MATERIAL_H
