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
#include "VectorMath.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

Model::Model(const char *obj_path, const char *uv_path, bool absolute_paths = false) {

    std::ifstream file;

    off_pos = new float[3];
    off_pos[0] = 0; off_pos[1] = 0; off_pos[2] = 0;


    off_rot = new float[3];
    off_rot[0] = 0; off_rot[1] = 0; off_rot[2] = 0;


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

    faces.push_back(face);
}

void Model::Display() {
    for(Face f : faces) {
        float p[3];

        if(parent == nullptr) {
            p[0] = pos[0] + off_pos[0];
            p[1] = pos[1] + off_pos[1];
            p[2] = pos[2] + off_pos[2];
        } else {
            float* parentPos = parent->position();
            p[0] = parentPos[0] + off_pos[0];
            p[1] = parentPos[1] + off_pos[1];
            p[2] = parentPos[2] + off_pos[2];
        }

        f.draw(p, off_rot, off_angle, scale);
    }
}

void Model::setOffsetPos(float x, float y, float z) {
    off_pos[0] = x;
    off_pos[1] = y;
    off_pos[2] = z;
}

void Model::setOffsetRot(float angle, float x, float y, float z) {
    off_rot[0] = x;
    off_rot[1] = y;
    off_rot[2] = z;
    off_angle = angle;
}

float *Model::position() {
    // copy the array from pos
    float* ret = new float[3];
    ret[0] = pos[0]; ret[1] = pos[1]; ret[2] = pos[2];

    // add the arrays to get our actual place in the world
    add(ret, off_pos, 1.0f);

    return ret;
}

// prevents error being thrown; since we have a similar position declaration here.
void Model::position(float x, float y, float z) {
    DisplayableObject::position(x, y, z);
}






