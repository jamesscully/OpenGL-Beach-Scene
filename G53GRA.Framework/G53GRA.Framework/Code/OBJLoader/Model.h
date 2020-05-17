//
// Created by yames on 4/5/20.
//

#ifndef G53GRA_FRAMEWORK_MODEL_H
#define G53GRA_FRAMEWORK_MODEL_H


#include <string>
#include <vector>
#include <Interface/Animation.h>

#include "Utils.h"
#include "Face.h"

#include "DisplayableObject.h"
#include "Material.h"

class Model : public DisplayableObject, Animation {

public:
    Model(const char *obj_name, const char *uv_path, bool absolute_paths, Model* parent = nullptr);
    ~Model() = default;

    void Display() override;

    // xyz offsets
    float* off_pos;
    float* off_rot;
    float  off_angle;
    float* off_scl;

    // we want it to be shiny

    float* uv_offset;


    Material* material = new Material();

    // this indicates that this model must follow where the parent is
    // ex: the palm tree leaves should always match the last log in the tree
    Model* parent = nullptr;

    void setOffsetPos(float x, float y, float z);
    void setOffsetRot(float angle, float x, float y, float z);
    void setOffsetUV(float x, float y);

    float *position() override;

    void position(float x, float y, float z) override;

    void setLighting(bool b);


private:

    std::string model_name = "default";

    std::string model_dir = "/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Models/";
    std::string model_suffix = ".obj";

    std::string uv_dir = "/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Models/UV/";
    std::string uv_suffix = ".bmp";
    void extractVertex(std::string line);
    void extractUV(std::string line);
    void extractNormal(std::string line);

    void extractFace(std::string line);

    void extractMtl(std::string line);

    GLuint texture = 0;

    std::vector<vertex>   vertices;
    std::vector<vertex2d> uvs;
    std::vector<vertex>   normals;
    std::vector<Face>     faces;

    void Update(const double &deltaTime) override;


    bool lighting = true;

};


#endif //G53GRA_FRAMEWORK_MODEL_H
