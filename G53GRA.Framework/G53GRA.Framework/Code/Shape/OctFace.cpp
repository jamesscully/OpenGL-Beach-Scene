//
// Created by yames on 2/19/20.
//

#include "OctFace.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <VectorMath.h>

OctFace::OctFace(float rot, float height, bool flip, int subdivLevel) {
    glPushMatrix();
    // modify in actual space
    glMatrixMode(GL_MODELVIEW);

    // we want to rotate around the up axis
    glRotatef(rot,0.0,1.0,0.0);

    float mid = height;

	float v1[3], v2[3], v3[3];

	// if flip, we draw from the highest point, (0, 100, 0)
	// else, we draw from the lowest point, (0,-100,0)
	if (flip) {
		v1[0] = 0;			v1[1] = 0 + mid;   v1[2] = 0;
		v2[0] = 0,          v2[1] = 0;         v2[2] = 0 - mid;
		v3[0] = 0 + -mid;	v3[1] = 0;         v3[2] = 0;
	} else {
		v1[0] = 0;			v1[1] = -mid; v1[2] = 0;
		v2[0] = 0 + -mid,   v2[1] = 0;    v2[2] = 0;
		v3[0] = 0;			v3[1] = 0;    v3[2] = 0 + -mid;
	}

    // return to projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();


    // subdivide this face
    subdivide(v1, v2, v3, subdivLevel);


}

OctFace::~OctFace() = default;


float* midpoint(const float a[], const float b[]) {

    // generate the mid point between each axis
	float x = (a[0] + b[0]) / 2;
	float y = (a[1] + b[1]) / 2;
	float z = (a[2] + b[2]) / 2;


	// combine them into new xyz coords
	float * ret = new float[3]{ x, y, z };

	// normalize so we have a unit vector of 1
	norm(ret);

	// scale to 100; pushes each midpoint out to the radius of the sphere
	scale(ret, 100.0f);

	return ret;
}

void OctFace::subdivide(float a[], float b[], float c[], int level)
{
    // once we've hit 0, we draw the triangle and return, ending recursion
	if (level == 0) {
		glBegin(GL_TRIANGLES);
			glColor3d(255, 0, 255);
			glVertex3f(a[0], a[1], a[2]);
			glVertex3f(b[0], b[1], b[2]);
			glVertex3f(c[0], c[1], c[2]);
		glEnd();
		glFlush();

		// draws a wireframe outline
		glBegin(GL_LINE_LOOP);
			glColor3d(0, 0, 0);
			glVertex3f(a[0], a[1], a[2]);
			glVertex3f(b[0], b[1], b[2]);
			glVertex3f(c[0], c[1], c[2]);
			glEnd();
		glFlush();
		return;
	}

	//     a
	//    / \
	//  t3 - t1
	//  /  \/  \
	// c - t2 - b

	float * t1 = midpoint(a, b);
	float * t2 = midpoint(b, c);
	float * t3 = midpoint(c, a);

	// draws the triangle from midpoints
    subdivide(t2, t3, t1, level - 1);

    // draws the triangles outside of the midpoints
    subdivide(c, t3, t2, level - 1);
    subdivide(t2, t1, b, level - 1);
    subdivide(t3, a, t1, level - 1);
}
