//
// Created by yames on 4/9/20.
//

#include <fstream>
#include "Material.h"

using std::string;

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
        // we want the first word,i.e. v to see what we're parsing
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
    ambient[0] = a, ambient[1] = b, ambient[2] = c;
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

    if(s > 255)
        s = 255;

    shiny[0] = s / 2;
    printf("\t\tExtracted Shininess Org: %f Rev: %f\n", s, shiny[0]);
}

void Material::extractEmission(std::string line) {
    float a, b, c;
    sscanf(line.c_str(), "%f %f %f", &a, &b, &c);
    emission[0] = a, emission[1] = b, emission[2] = c;
    printf("\t\tExtracted Emission: %f %f %f\n", emission[0], emission[1], emission[2]);
}


