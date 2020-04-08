//
// Created by yames on 4/5/20.
//

#include <cstring>
#include <fstream>
#include <strstream>
#include <iostream>
#include <GL/gl.h>
#include "Model.h"
#include "Face.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

Model::Model(const char *file_name) {


    std::ifstream file;
    file.open(file_name);


    // add cerr output

    string line;
    while(!file.eof()) {
        string first;
        getline(file, line);
        // we want the first word,i.e. v to see what we're parsing
        first = line.substr(0, line.find(" "));

        // then, we don't need the type
        line = line.substr(first.length(), line.length());

        // add ignoring comments
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

void Model::parseFile(std::ifstream f) {

}

void Model::extractVertex(std::string line) {

    //printf("ev: parsing line: %s\n", line.c_str());
    float x = 0, y = 0, z = 0;

    sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

    vertex add {x, y, z};

    vertices.push_back(add);

    printf("found vertex: (%f, %f, %f)\n", x, y, z);
}

void Model::extractNormal(std::string line) {
    //printf("vn: parsing line: %s\n", line.c_str());
    float x = 0, y = 0, z = 0;

    sscanf(line.c_str(), "%f %f %f", &x, &y, &z);

    vertex add {x, y, z};

    normals.push_back(add);

    printf("found normal: (%f, %f, %f)\n", x, y, z);
}

void Model::extractUV(std::string line) {
    // printf("vt: parsing line: %s\n", line.c_str());
    float x = 0, y = 0;

    sscanf(line.c_str(), "%f %f", &x, &y);

    uv_coord add {x, y};

    uvs.push_back(add);

    // printf("found uv: (%f, %f)\n", x, y);
}

void Model::extractFace(std::string line) {
    Face face;

    int v1,  v2,  v3;
    int vt1, vt2, vt3;
    int vn1, vn2, vn3;

    // example line : v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ..
    sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);

    face.v1 = vertices.at(v1 - 1); face.v2 = vertices.at(v2 - 1); face.v3 = vertices.at(v3 - 1);
    face.vt1 = uvs.at(vt1 - 1); face.vt2 = uvs.at(vt2 - 1); face.vt3 = uvs.at(vt3 - 1);


    printf("Adding face: %f %f %f\n", face.v1.x,  face.v1.y,  face.v1.z);
    printf("Adding face: %f %f %f\n", face.v2.x,  face.v2.y,  face.v2.z);
    printf("Adding face: %f %f %f\n", face.v3.x,  face.v3.y,  face.v3.z);

    faces.push_back(face);
}

void Model::draw() {
    glBegin(GL_LINE_LOOP);

    for(Face f : faces) {
        f.draw();
    }

    glEnd();
}



