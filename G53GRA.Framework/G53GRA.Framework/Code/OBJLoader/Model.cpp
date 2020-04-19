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

Model::Model(const char *obj_path, const char *uv_path, bool absolute_paths = false) {

    std::ifstream file;

    offset = new float[3];
    offset[0] = 0; offset[1] = 0; offset[2] = 0;

    if(absolute_paths) {
        printf("Loading Model with paths: \n\t%s\n\t%s\n", obj_path, uv_path);
        file.open(obj_path);
        texture = Scene::GetTexture(uv_path);
    }
    else {
        printf("Loading Model with paths: \n\t%s\n\t%s\n", (model_dir + obj_path).c_str(), (model_dir + uv_path).c_str());
        file.open(model_dir + obj_path);
        texture = Scene::GetTexture(model_dir + uv_path);
    }

    if(!file.good())
        printf("Error: error loading model file\n");
    else
        printf("\tSuccessfuly loaded the model file\n");

    // add cerr output

    string line;

    printf("\tExtracting data\n");
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
    printf("Finished extracting data\n");
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

//    printf("Adding face: %f %f %f\n", face.v1.x,  face.v1.y,  face.v1.z);
//    printf("Adding face: %f %f %f\n", face.v2.x,  face.v2.y,  face.v2.z);
//    printf("Adding face: %f %f %f\n", face.v3.x,  face.v3.y,  face.v3.z);

    faces.push_back(face);
}

void Model::Display() {
    for(Face f : faces) {

        float p[3] = {pos[0] + offset[0],
                      pos[1] + offset[1],
                      pos[2] + offset[2]};

        f.draw(p, rotation, scale);
    }
}

void Model::setOffset(float x, float y, float z) {
    offset[0] = x;
    offset[1] = y;
    offset[2] = z;
}



