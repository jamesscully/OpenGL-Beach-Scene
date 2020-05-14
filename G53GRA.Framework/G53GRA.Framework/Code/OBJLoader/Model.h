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
    Model(const char *obj_path, const char *uv_path, bool absolute_paths, Model* parent = nullptr);
    ~Model() = default;

    void Display() override;

    // xyz offsets
    float* off_pos;
    float* off_rot;
    float  off_angle;
    float* off_scl;



    // this indicates that this model must follow where the parent is
    // ex: the palm tree leaves should always match the last log in the tree
    Model* parent = nullptr;

    // should we adhere to the parent's attributes?
    bool p_pos = false, p_rot = false, p_scl = false;

    void setOffsetPos(float x, float y, float z);
    void setOffsetRot(float angle, float x, float y, float z);

    float *position() override;

    void position(float x, float y, float z) override;

private:

    std::string model_dir = "/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Models/";
    void extractVertex(std::string line);
    void extractUV(std::string line);
    void extractNormal(std::string line);

    void extractFace(std::string line);

    GLuint texture;

    std::vector<vertex>   vertices;
    std::vector<vertex2d> uvs;
    std::vector<vertex>   normals;
    std::vector<Face>     faces;
};


#endif //G53GRA_FRAMEWORK_MODEL_H
