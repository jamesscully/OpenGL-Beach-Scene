//
// Created by yames on 4/5/20.
//

#ifndef G53GRA_FRAMEWORK_MODEL_H
#define G53GRA_FRAMEWORK_MODEL_H


#include <string>
#include <vector>

#include "Utils.h"
#include "Face.h"

#include "DisplayableObject.h"

class Model : public DisplayableObject {

public:
    Model(const char *obj_path, const char *uv_path, bool absolute_paths);
    ~Model() = default;

    void Display() override;


private:

    std::string model_dir = "/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Models/";
    void extractVertex(std::string line);
    void extractUV(std::string line);
    void extractNormal(std::string line);

    void extractFace(std::string line);

    GLuint texture;

    std::vector<vertex>   vertices;
    std::vector<uv_coord> uvs;
    std::vector<vertex>   normals;
    std::vector<Face>     faces;

};


#endif //G53GRA_FRAMEWORK_MODEL_H
