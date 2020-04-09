//
// Created by yames on 4/5/20.
//

#include <cstring>
#include <fstream>
#include <strstream>
#include <iostream>
#include <Engine/Scene.h>
#include "Model.h"
#include "Face.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

Model::Model(const char *file_name, const char * uv_map) {

    std::ifstream file;
    file.open(file_name);

    texture = Scene::GetTexture(uv_map);

    // add cerr output

    string line;
    while(!file.eof()) {
        string first;
        getline(file, line);
        // we want the first word,i.e. v to see what we're parsing
        first = line.substr(0, line.find(" "));

        // then, we don't need the type
        line = line.substr(first.length(), line.length());

        // printf("first : %s out of line: %s\n", first.c_str(), line.c_str());

        if(first == "v")
            extractVertex(line);
        else if (first == "vn")
            extractNormal(line);
        else if (first == "f")
            extractFace(line);
        else if (first == "vt")
            extractUV(line);
    }
}

void Model::extractVertex(std::string line) {
    float x = 0, y = 0, z = 0;
    sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
    vertex add {x, y, z};
    vertices.push_back(add);
}

void Model::extractNormal(std::string line) {
    float x = 0, y = 0, z = 0;
    sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
    vertex add {x, y, z};
    normals.push_back(add);
}

void Model::extractUV(std::string line) {
    float x = 0, y = 0;
    sscanf(line.c_str(), "%f %f", &x, &y);
    uv_coord add {x, y};
    uvs.push_back(add);
}

void Model::extractFace(std::string line) {
    Face face(&texture);

    // given that we would have already extracted v, vn and vts, these are the indices from our vectors vertices/uv/normals
    int v1,  v2,  v3;
    int vt1, vt2, vt3;
    int vn1, vn2, vn3;

    // example line : v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ..
    sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);

    // get the vertices from the id
    face.v1 = vertices.at(v1 - 1); face.v2 = vertices.at(v2 - 1); face.v3 = vertices.at(v3 - 1);
    face.vt1 = uvs.at(vt1 - 1); face.vt2 = uvs.at(vt2 - 1); face.vt3 = uvs.at(vt3 - 1);
    face.vn1 = normals.at(vn1 - 1); face.vn2 = normals.at(vn2 - 1); face.vn3 = normals.at(vn3 - 1);

    printf("Adding face: %f %f %f\n", face.v1.x,  face.v1.y,  face.v1.z);
    printf("Adding face: %f %f %f\n", face.v2.x,  face.v2.y,  face.v2.z);
    printf("Adding face: %f %f %f\n", face.v3.x,  face.v3.y,  face.v3.z);

    faces.push_back(face);
}

void Model::Display() {
    for(Face f : faces) {
        f.draw(pos, rotation, scale);
    }
}



