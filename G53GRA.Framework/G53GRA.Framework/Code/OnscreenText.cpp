#include "OnscreenText.h"
#include <GL/glut.h>

using std::string;

OnscreenText::OnscreenText(int nX, int nY, string text)
{
    x = nX;
    y = nY;
    str = text;
}

OnscreenText::~OnscreenText()
{
    //dtor
}

void OnscreenText::setPos(int nX, int nY)
{
    x = nX;
    y = nY;
}

void OnscreenText::setText(std::string s)
{
    str = s;
}

void OnscreenText::setFont(void* fnt)
{
    font = fnt;
}

void OnscreenText::render()
{
    int len = str.length();

    glDisable(GL_LIGHTING);
    glMatrixMode( GL_PROJECTION );
    glColor3f(255, 0, 0);

    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0, 1280, 0, 1024 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);  // move in 10 pixels from the left and bottom edges

    for ( int i = 0; i < len; ++i ) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
    glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_LIGHTING);
}



