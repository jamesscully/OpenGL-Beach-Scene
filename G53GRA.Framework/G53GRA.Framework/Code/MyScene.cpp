#include "MyScene.h"
#include "Wall.h"
#include "OnscreenText.h"
#include "Light.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

Light *light1, *light2;

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
    WIN_HEIGHT = windowHeight;
    WIN_WIDTH  = windowWidth;
}

void MyScene::Initialise()
{
    float colorScale = 0.0f;
	glClearColor(colorScale, colorScale, colorScale, 1.0f);

    Wall *wall = new Wall();
    wall->size(50);

    light1 = new Light(GL_LIGHT0);
    light2 = new Light(GL_LIGHT1);

    light1->position(20, 0, 10);
    light2->position(-20, 0, 10);

    light1->setColor(2, 0, 0);
    light2->setColor(0, 0, 2);

    AddObjectToScene(wall);

    AddObjectToScene(light1);
    AddObjectToScene(light2);
}

void MyScene::Projection() {
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 1000.0);


    drawAxisLines();
    drawDebugText();
}

int x_off = 20;

OnscreenText hlpText(x_off, 50, "[linear att: j/k] [constant att: n/m] [quad att: h/l]   reset = x");

void MyScene::drawDebugText() {
    hlpText.render();
}


void MyScene::HandleKey(unsigned char key, int state, int x, int y) {
    light1->HandleKey(key, state, x, y);
    light2->HandleKey(key, state, x, y);
}

// Miscellaneous grid-drawing functions

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
        glutSolidSphere(1, 25, 25);
        glTranslated(0, 0, 0);
    glPopMatrix();

}






