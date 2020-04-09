//
// Created by yames on 4/8/20.
//

#include <GL/gl.h>
#include "Face.h"

Face::Face(GLuint *uv) {
    texture = uv;
}

void Face::draw(float* pos, float* rot, float* scale) {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glBindTexture(GL_TEXTURE_2D, *texture);

    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
//    glRotatef(rot[0], rot[1], rot[2]);
    glBegin(GL_TRIANGLES);
        // if we're using a texture, we'll want the base colour to be white
        glColor3f(255, 255, 255);
        glTexCoord2f(vt1.x, vt1.y);
        glNormal3f(vn1.x, vn1.y, vn1.z);
        glVertex3f(v1.x, v1.y, v1.z);

        glTexCoord2f(vt2.x, vt2.y);
        glNormal3f(vn2.x, vn2.y, vn2.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glTexCoord2f(vt3.x, vt3.y);
        glNormal3f(vn3.x, vn3.y, vn3.z);
        glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
    glPopMatrix();



    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
