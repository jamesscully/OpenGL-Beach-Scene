//
// Created by yames on 4/8/20.
//

#include <GL/gl.h>
#include "Face.h"

Face::Face(GLuint *uv) {
    texture = uv;
}

void Face::draw(float *pos, float *rot, float *scale, float *uv_offsets, bool lighting) {


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    if(lighting)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, *texture);

    vt1.x += uv_offsets[0]; vt1.y += uv_offsets[1];
    vt2.x += uv_offsets[0]; vt2.y += uv_offsets[1];
    vt3.x += uv_offsets[0]; vt3.y += uv_offsets[1];

    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);

    // rotate in each XYZ
    glRotatef(rot[0], rot[0],  0, 0);
    glRotatef(rot[1], 0,  rot[1], 0);
    glRotatef(rot[2], 0,  0, rot[2]);

    glBegin(GL_TRIANGLES);
        // if we're using a texture, we'll want the base colour to be white
        glColor3f(255, 255, 255);

        // load each v1 v2 v3 data points (tex/norms/pos)
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
