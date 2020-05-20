#include <Skybox/Skybox.h>
#include <Ocean/Ocean.h>
#include <OBJLoader/Model.h>
#include <DayNight/Sun.h>
#include <DayNight/Moon.h>
#include <ModelGroups/PalmTree/PalmTree.h>
#include <ModelGroups/Docks/DockBase.h>
#include "MyScene.h"
#include "OnscreenText.h"
#include "Projectile.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
    WIN_HEIGHT = windowHeight;
    WIN_WIDTH  = windowWidth;
}

// we'll declare pointers here, so that we can access them from different functions (helps not hiding everything in header)

Sun * sun; Moon * moon;

Skybox* skybox;
Ocean* ocean;
Model * island;
PalmTree* palmTree;
DockBase* dock;


void MyScene::Initialise() {

    island = new Model("island", "island_texture", false); {
        island->position(0, 60, 0);
        AddObjectToScene(island);
    }

    ocean = new Ocean();
    ocean->size(10000);
//    AddObjectToScene(ocean);

    // any likely changes to background will be a 'shade' rather than specific colour
    float colorScale = 0.0f;
	glClearColor(colorScale, colorScale, colorScale, 1.0f);

    skybox = new Skybox(); {
        skybox->size(1000);
        skybox->position(0, -10, 0);
        AddObjectToScene(skybox);
    }

    // changes speed of both sun/moon
    float cyclespeed = 0.2;

    glDisable(GL_LIGHTING);

    sun = new Sun(GL_LIGHT1); {
        sun->position(0, 0, 0);
        sun->radius = 600;
        sun->speed = cyclespeed;
        AddObjectToScene(sun);
    }

    moon = new Moon(GL_LIGHT2); {
        moon->position(0, 0, 0);
        moon->radius = 600;
        moon->speed = cyclespeed;
        // we want the moon to be opposite of the sun
        moon->inverted = true;
        AddObjectToScene(moon);
    }

    palmTree = new PalmTree(); {
        palmTree->position(0, 50, 0);
        AddObjectToScene(palmTree);
    }

    dock = new DockBase(); {
        AddObjectToScene(dock);
    }




}

void MyScene::Projection() {
    glDisable(GL_LIGHT0);

    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 10000.0);

    // drawDebugText();
    // drawAxisLines();

    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
}

Model* projectileModel;
void MyScene::HandleMouse(int button, int state, int x, int y) {

    // Right mouse throws coconuts
    if(button == GLUT_RIGHT_BUTTON && state == 1) {

        // if we haven't constructed the model, do so
        // this will prevent us constantly creating new Models (thus potentially leaking more memory)
        if(projectileModel == nullptr)
            projectileModel = new Model("coconut", "coconut", false);

        // pass camera at current point to get forward direction
        auto* projectile = new Projectile(&camera);

        // pass the model's pointer
        projectile->setModel(projectileModel);

        AddObjectToScene(projectile);
    }
}

bool CURSOR_LOCKED = true;

void MyScene::HandleMouseMove(int x, int y) {
    // if the cursor is locked, then we act as if we're dragging usually
    if(CURSOR_LOCKED)
        Scene::HandleMouseDrag(x, y);
}

void MyScene::HandleKey(unsigned char key, int state, int x, int y) {
    sun->HandleKey(key, state, x, y);

    // if ESC is hit, lock cursor
    if(key == 27 && state == 1) {
        printf("Cursor Locked: %d", CURSOR_LOCKED);

        if(CURSOR_LOCKED)
            glutSetCursor(GLUT_CURSOR_INHERIT);
        else
            glutSetCursor(GLUT_CURSOR_NONE);

        CURSOR_LOCKED = !CURSOR_LOCKED;
    } else {
        Scene::HandleKey(key, state, x, y);
    }
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
