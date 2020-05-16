//
// Created by yames on 4/9/20.
//

#include <fstream>
#include "Material.h"

using std::string;

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
        else if (first == "d" || first == "Tr") {
            extractTransparency(line, first == "Tr");
        }
    }

    printf("\tFinished Extracting Material\n");
}

void Material::extractAmbient(std::string line) {
    printf("\t\tFound Ambient: %s\n", line.c_str());
}

void Material::extractDiffuse(std::string line) {
    printf("\t\tFound Diffuse: %s\n", line.c_str());
}

void Material::extractSpecular(std::string line) {
    printf("\t\tFound Specular: %s\n", line.c_str());
}

void Material::extractTransparency(std::string line, bool invert) {
    printf("\t\tFound Transparency: %s\n", line.c_str());
}

Material::~Material() = default;
