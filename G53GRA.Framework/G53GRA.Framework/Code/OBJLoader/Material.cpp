//
// Created by yames on 4/9/20.
//

#include <fstream>
#include "Material.h"

using std::string;

#pragma warning(disable:4996)


// Example MTL file:
/*
# Blender MTL File : 'island.blend'
# Material Count : 1

newmtl Wood
Ns 0.000000 - Shininess
Ka 0.147000 0.132000 0.068000 - Ambient color
Kd 0.147000 0.132000 0.068000 - Diffuse color
Ks 0.147000 0.132000 0.068000 - Specular color
Ke 0.000000 0.000000 0.000000 - Emission color
Ni 1.450000 - ??
d 1.000000 - Transparency (can also be Tr)
illum 2 - Used in external programs for combining illumination models
*/




Material::Material() {

}
Material::~Material() = default;

Material::Material(std::string path) {
    printf("\tExtracting Material: %s\n", path.c_str());
    std::ifstream file;

    file.open(path);

    string line = "";
    while(!file.eof()) {
        string first;
        getline(file, line);
        // we want the first word to see what we're parsing
        first = line.substr(0, line.find(" "));

        // then, we don't need the type
        line = line.substr(first.length(), line.length());

        // printf("first : %s out of line: %s\n", first.c_str(), line.c_str());

        if(first == "Ka")
            extractAmbient(line);
        else if (first == "Kd")
            extractDiffuse(line);
        else if (first == "Ks")
            extractSpecular(line);
        else if (first == "Ns")
            extractShininess(line);
        else if (first == "Ke")
            extractEmission(line);
        else if (first == "d" || first == "Tr") {
            extractTransparency(line, first == "Tr");
        } else if (first == "newmtl") {
            name = line;
        }
    }

    printf("\tFinished Extracting Material\n");
}

void Material::extractAmbient(std::string line) {
    float a, b, c;
    sscanf(line.c_str(), "%f %f %f", &a, &b, &c);
    // ambient[0] = a, ambient[1] = b, ambient[2] = c;

    // weird glitches occuring with Blender exports - they seem to all default to 1,1,1
    ambient[0] = 0, ambient[1] = 0, ambient[2] = 0;
    printf("\t\tExtracted Ambient: %f %f %f\n", a, b, c);
}

void Material::extractDiffuse(std::string line) {
    float a, b, c;
    sscanf(line.c_str(), "%f %f %f", &a, &b, &c);
    diffuse[0] = a, diffuse[1] = b, diffuse[2] = c;
    printf("\t\tExtracted Diffuse: %f %f %f\n", a, b, c);
}

void Material::extractSpecular(std::string line) {
    float a, b, c;
    sscanf(line.c_str(), "%f %f %f", &a, &b, &c);
    specular[0] = a, specular[1] = b, specular[2] = c;
    printf("\t\tExtracted Specular: %f %f %f\n", a, b, c);
}

void Material::extractTransparency(std::string line, bool invert) {
    sscanf(line.c_str(), "%f", &transparency);

    // OBJ Tr = inverted | d = normal
    if(invert)
        transparency = 1 - transparency;

    diffuse[3] = transparency;
    ambient[3] = transparency;
    specular[3] = transparency;

    printf("\t\tExtracted Transparency: %f\n", transparency);
}

void Material::extractShininess(std::string line) {
    float s = 0;
    sscanf(line.c_str(), "%f", &s);

    // clamp values greater than 255
    if(s > 255)
        s = 255;

    // max value for opengl is 128 - divide by 2 
    shiny[0] = s / 2;
    shiny[0] = 0;
    printf("\t\tExtracted Shininess Org: %f Rev: %f\n", s, shiny[0]);
}

void Material::extractEmission(std::string line) {
    float a, b, c;
    sscanf(line.c_str(), "%f %f %f", &a, &b, &c);
    emission[0] = a, emission[1] = b, emission[2] = c;
    printf("\t\tExtracted Emission: %f %f %f\n", emission[0], emission[1], emission[2]);
}


