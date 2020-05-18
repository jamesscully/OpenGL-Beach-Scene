#include <Island/Island.h>
#include <Skybox/Skybox.h>
#include <Ocean/Ocean.h>
#include <Oct/Octahedron.h>
#include <OBJLoader/Model.h>
#include <PalmTree/PalmTree.h>
#include <DayNight/Sun.h>
#include "MyScene.h"
#include "OnscreenText.h"
#include "Light.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
    WIN_HEIGHT = windowHeight;
    WIN_WIDTH  = windowWidth;
}

// we'll declare pointers here, so that we can access them from different functions (helps not hiding everything in header)

Sun * sun;
Model * island;
Skybox* skybox;
Ocean* ocean;
Octahedron* octahedron;
Model * model;
PalmTree* ptree;

Model* tex_model;
void MyScene::Initialise() {

    octahedron = new Octahedron(100, 1);

    // any likely changes to background will be a 'shade' rather than specific colour
    float colorScale = 0.0f;
	glClearColor(colorScale, colorScale, colorScale, 1.0f);

    skybox = new Skybox();
    skybox->size(1000);
    skybox->position(0, -10, 0);
    AddObjectToScene(skybox);

    sun = new Sun(GL_LIGHT1);
//    sun->position(0, 990, 0);
    sun->position(0, 300, 0);
    AddObjectToScene(sun);

    island = new Model("island", "", false);
    island->position(0, 20, 0);
    island->size(10);
    island->setLighting(true);
    AddObjectToScene(island);

    ptree = new PalmTree();
    ptree->position(0, 10000, 0);
    AddObjectToScene(ptree);

    ocean = new Ocean();
    ocean->size(10000);
    AddObjectToScene(ocean);

    tex_model = new Model("test", "", false);
    tex_model->position(0, 0, 0);
    tex_model->size(10);
    AddObjectToScene(tex_model);


}

void MyScene::Projection() {

    glDisable(GL_LIGHT0);

    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 10000.0);

    //drawDebugText();
//    drawAxisLines();

    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

}

void MyScene::HandleKey(unsigned char key, int state, int x, int y) {
    sun->HandleKey(key, state, x, y);
    Scene::HandleKey(key, state, x, y);
}

//
// Miscellaneous grid-drawing functions
//
void MyScene::drawGridLines() {

    int MAX_X = 2000;
    int MAX_Z = 2000;

    // since they will intersect eachother, we can simply define a size, so this would be in units
    int SIZE = 50;
    glBegin(GL_LINES);

    float scale = 0.5;
    glColor3f(scale, scale, scale);

    for(int i = -1000; i < 1000; i += SIZE) {
        glVertex3i( MAX_X, 0, i);
        glVertex3i(-MAX_X, 0, i);

        glVertex3i(i, 0,  MAX_Z);
        glVertex3i(i, 0, -MAX_Z);
    }

    glEnd();
}
void MyScene::drawAxisLines() {
    // draw the grid lines first, that way axis are overlaid
    drawGridLines();

    int MAX_X = 2000;
    int MAX_Z = 2000;

    glBegin(GL_LINES);
    // draw our main X axis
    glColor3f(2,0,0);
    glVertex3d(MAX_X, 0, 0);
    glVertex3d(-MAX_X, 0, 0);

    // draw our main Z axis
    glColor3f(0,2,0);
    glVertex3d(0, 0, MAX_Z);
    glVertex3d(0, 0, -MAX_Z);
    glEnd();
    glFlush();

    // draw center dot
    glPushMatrix();
    glColor3f(0, 0, 255);
    // glutSolidSphere(1, 25, 25);
    glTranslated(0, 0, 0);
    glPopMatrix();
}
