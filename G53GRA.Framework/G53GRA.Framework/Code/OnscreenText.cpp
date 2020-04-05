#include "OnscreenText.h"
#include <GL/glut.h>

using std::string;

OnscreenText::OnscreenText(int nX, int nY, string text)
{
    x = nX;
    y = nY;
    str = text;
    has_value = false;
}

OnscreenText::OnscreenText(int nX, int nY, std::string text, float* value) {
    x = nX; y = nY;
    str = text;

    has_value = true;
    this->value = value;
}

OnscreenText::~OnscreenText() = default;

void OnscreenText::render()
{
    glDisable(GL_LIGHTING);
    glMatrixMode( GL_PROJECTION );
    glColor3f(255, 0, 0);

    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0, 1366, 0, 786 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);  // move in 10 pixels from the left and bottom edges

    // we'll want to display str in the case we don't have a value
    string out = str;

    // if we have a value, append it.
    if(has_value)
        out = out + " " + std::to_string(*value);

    int len = out.length();
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, out[i]);
    }

    glPopMatrix();

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_LIGHTING);
}





