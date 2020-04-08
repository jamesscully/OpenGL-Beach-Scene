#include <Island/Island.h>
#include <Logs/LogA.h>
#include <Skybox/Skybox.h>
#include <Ocean/Ocean.h>
#include <Oct/Octahedron.h>
#include <OBJLoader/Model.h>
#include "MyScene.h"
#include "OnscreenText.h"
#include "Light.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// we'll declare pointers here, so that we can access them from different functions (helps not hiding everything in header)
Light * light1, *light2;

Island * island;

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
    WIN_HEIGHT = windowHeight;
    WIN_WIDTH  = windowWidth;
}


LogA* logA;

Skybox* skybox; Ocean* ocean;
Octahedron* octahedron;

Model * model;
void MyScene::Initialise() {

    octahedron = new Octahedron(100, 1);

    // any likely changes to background will be a 'shade' rather than specific colour
    float colorScale = 1.0f;
	glClearColor(colorScale, colorScale, colorScale, 1.0f);

    light1 = new Light(GL_LIGHT0);
    light1->position(20, 50, 10);
    light1->setColor(2, 0, 0);

    //logA = new LogA();
    //AddObjectToScene(logA);



    model = new Model("/mnt/data/home/untitled.obj");

//    skybox = new Skybox();
//    skybox->size(10000);
//
//    ocean = new Ocean();
//    ocean->size(10000);
//
//    AddObjectToScene(skybox);
//    AddObjectToScene(ocean);
//
//    AddObjectToScene(light1);

}

int x_off = 20;
OnscreenText hlpText(x_off, 50, "[linear att: <j  k>] [constant att: <n m>] [quad att: <h l>]   reset = x");

void MyScene::drawDebugText() {
    hlpText.render();
}


int SUBDIVIDE_LEVEL = 5;
float HEIGHT = 300;
Octahedron oct(HEIGHT, SUBDIVIDE_LEVEL);

void MyScene::Projection() {
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 10000.0);

    //drawDebugText();
    drawAxisLines();
    model->draw();
    // oct.draw();
}

void MyScene::HandleKey(unsigned char key, int state, int x, int y) {

//    switch (key) {
//        case 'q':
//            if(wall->SUB_SCALE > 1)
//                wall->SUB_SCALE -= 1;
//            break;
//
//        case 'e':
//            wall->SUB_SCALE += 1;
//            break;
//    }
//
//    // pass key events to lights, so they can deal with atten. changes
//    light1->HandleKey(key, state, x, y);
//    light2->HandleKey(key, state, x, y);



    Scene::HandleKey(key, state, x, y);
}


//
//
// Miscellaneous grid-drawing functions
//
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