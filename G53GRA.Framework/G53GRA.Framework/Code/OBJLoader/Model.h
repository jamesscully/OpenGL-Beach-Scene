//
// Created by yames on 4/5/20.
//

#ifndef G53GRA_FRAMEWORK_MODEL_H
#define G53GRA_FRAMEWORK_MODEL_H


#include <string>
#include <vector>
#include "Utils.h"
#include "Face.h"


class Model {



public:
    Model(const char *file_name);
    ~Model() = default;


    void draw();

private:
    void parseFile(std::ifstream f);

    void extractVertex(std::string line);
    void extractUV(std::string line);
    void extractNormal(std::string line);

    void extractFace(std::string line);

    std::vector<vertex>   vertices;
    std::vector<uv_coord> uvs;
    std::vector<vertex>   normals;
    std::vector<Face>   faces;

};


#endif //G53GRA_FRAMEWORK_MODEL_H
