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
    Model(const char *obj_path, const char *uv_path, bool absolute_paths, Model* parent = nullptr);
    ~Model() = default;

    void Display() override;

    // xyz offsets
    float* off_pos;
    float* off_rot;
    float  off_angle;
    float* off_scl;

    bool lighting;


    float ambient[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    float diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    float SPEC_SHADE = 0.5f;
    float specular[4] = { SPEC_SHADE, SPEC_SHADE, SPEC_SHADE, 1.0f};

    // we want it to be shiny
    float shiny[1] = {0.0f};

    Material* material;


    float* uv_offset;



    // this indicates that this model must follow where the parent is
    // ex: the palm tree leaves should always match the last log in the tree
    Model* parent = nullptr;

    // should we adhere to the parent's attributes?
    bool p_pos = false, p_rot = false, p_scl = false;

    void setOffsetPos(float x, float y, float z);
    void setOffsetRot(float angle, float x, float y, float z);
    void setOffsetUV(float x, float y);

    float *position() override;

    void position(float x, float y, float z) override;

private:

    std::string model_dir = "/mnt/data/home/coursework/y3/gra/final/g53gra_framework/G53GRA.Framework/G53GRA.Framework/Models/";
    void extractVertex(std::string line);
    void extractUV(std::string line);
    void extractNormal(std::string line);

    void extractFace(std::string line);

    void extractMtl(std::string line);

    GLuint texture;

    std::vector<vertex>   vertices;
    std::vector<vertex2d> uvs;
    std::vector<vertex>   normals;
    std::vector<Face>     faces;

    void Update(const double &deltaTime) override;


    void setLighting(bool b);
};


#endif //G53GRA_FRAMEWORK_MODEL_H
