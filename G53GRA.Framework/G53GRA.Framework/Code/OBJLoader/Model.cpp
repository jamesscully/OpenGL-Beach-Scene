//
// Created by yames on 4/5/20.
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma warning(disable:4996)

// Example .obj file (truncated)
/*
# Blender v2.82 (sub 7) OBJ File: 'moonthing.blend'
# www.blender.org
o Circle - Metadata; Blender writes whatever the name of the object is
v 0.073151 0.998844 0.628936 - Vertex point (X, Y, Z)
v 0.073151 0.922724 0.519221
...
vt 0.000000 0.000000 - UV coordinate (X,Y)
vt 0.000000 0.000000
...
vn -0.7244 -0.5209 0.4516 - Vertex Normal (X, Y, Z)
vn -0.8243 -0.3401 0.4527
...
f 31/1/1 3/2/1 2/3/1 - Face, each segment is v1/vt1/vn1 or vertex/uv/normal.
f 32/4/2 4/5/2 3/2/2 - These are indices, so the above data must be stored into arrays
*/

#include <cstring>
#include <fstream>
#include <strstream>
#include <iostream>
#include <Engine/Scene.h>
#include "Model.h"
#include "Face.h"
#include "VectorMath.h"
#include <GL/glut.h>


using std::string;
using std::cout;
using std::cin;
using std::endl;

#ifdef _MSC_VER
#include <direct.h>
#endif


Model::Model(const char *obj_name, const char *uv_name, bool absolute_paths = false, Model* parent) {

    std::ifstream file;

    string test = uv_name;

    // if absolute paths are set, we trust the user and try load that file
    if(absolute_paths) {
        printf("Loading Model with paths: \n\t%s\n\t%s\n", obj_name, uv_name);
        file.open(obj_name);

        if(uv_name != "")
            texture = Scene::GetTexture(uv_name);
    }
    // else fetch from model/uv dir specified in header
    else {
        printf("Loading Model with paths: \n\tObj: %s\n\tTex: %s\n", (model_dir + obj_name).c_str(), (model_dir + uv_name).c_str());

        file.open(model_dir + obj_name + model_suffix);

        if(uv_name != "")
            texture = Scene::GetTexture(uv_dir + uv_name + uv_suffix);

        model_name = obj_name;
    }

    // don't load this object if we can't find the model
    if (!file.good()) {
        printf("Error: Couldn't load model file\n");
        return;
    }
    else {
        printf("\tSuccessfuly loaded the model file\n");
    }

    // add cerr output

    string line;

    printf("\tExtracting data\n");

    while(!file.eof()) {

        // stored the first word (v, vt, vn, f, o .. etc)
        string first;
        getline(file, line);


        // we want the first word, i.e. v to see what we're parsing
        first = line.substr(0, line.find(" "));

        // then, we don't need the type
        line = line.substr(first.length(), line.length());

        if(first == "v")
            extractVertex(line);
        else if (first == "vn")
            extractNormal(line);
        else if (first == "f")
            extractFace(line);
        else if (first == "vt")
            extractUV(line);
        else if (first == "usemtl" || first == "mtllib")
            extractMtl(line);
    }
    printf("Finished extracting data\n");
}

void Model::extractMtl(std::string line) {
    char mat_name[16];

    // read our mat name from line
    sscanf(line.c_str(), "%s", mat_name);

    // if we have no material, return
    if(strcmp(mat_name, "None") == 0)
        return;

    line = line.substr(0, line.find("."));
    
    // log it
    printf("\tFound Material: %s\n\t", mat_name);

    this->material = new Material(model_dir + model_name + ".mtl");
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
    vertex2d add {x, y};
    uvs.push_back(add);
}

void Model::extractFace(std::string line) {
    Face face(&texture);

    // given that we would have already extracted v, vn and vts, pull them and merge to make a face obj
    int v1,  v2,  v3;
    int vt1, vt2, vt3;
    int vn1, vn2, vn3;

    // example obj line : v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ..
    sscanf(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);

    // get the vertices from the id
    face.v1 = vertices.at(v1 - 1);  face.v2 = vertices.at(v2 - 1); face.v3 = vertices.at(v3 - 1);
    face.vt1 = uvs.at(vt1 - 1);     face.vt2 = uvs.at(vt2 - 1); face.vt3 = uvs.at(vt3 - 1);
    face.vn1 = normals.at(vn1 - 1); face.vn2 = normals.at(vn2 - 1); face.vn3 = normals.at(vn3 - 1);

    faces.push_back(face);
}

void Model::setLighting(bool b) {
    lighting = b;
}

void Model::Display() {
    for(Face f : faces) {
        float p[3];

        // if we're not parented, then use the base pos[] + offset arrays
        if(parent == nullptr) {
            p[0] = pos[0] + off_pos[0];
            p[1] = pos[1] + off_pos[1];
            p[2] = pos[2] + off_pos[2];
        }
        // if we are parented, add the parent pos and our pos
        else {
            float* parentPos = parent->position();
            p[0] = parentPos[0] + pos[0];
            p[1] = parentPos[1] + pos[1];
            p[2] = parentPos[2] + pos[2];
        }

        f.draw(p, rotation, scale, uv_offset, lighting, this->material);
    }
}

// when we want to offset the position
void Model::setOffsetPos(float x, float y, float z) {
    off_pos[0] = x;
    off_pos[1] = y;
    off_pos[2] = z;
}

// set offset for UV, so we can animate this model
void Model::setOffsetUV(float x, float y) {
    uv_offset[0] = (uv_offset[0] >= 1) ? 0 : x; uv_offset[1] = (uv_offset[1] >= 1) ? 0 : y;
}


// 'buffer', so we can add current pos + offset
float ret[3] = {0, 0, 0};
float *Model::position() {
    ret[0] = pos[0]; 
    ret[1] = pos[1]; 
    ret[2] = pos[2];

    // add the arrays to get our actual place in the world
    add(ret, off_pos, 1.0f);

    return ret;
}

// prevents error being thrown; since we have overloaded the other pos func here.
void Model::position(float x, float y, float z) {
    DisplayableObject::position(x, y, z);
}

void Model::Update(const double &deltaTime) {

}







