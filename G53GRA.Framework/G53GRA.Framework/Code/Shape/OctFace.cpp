//
// Created by yames on 2/19/20.
//

#include "OctFace.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <VectorMath.h>

OctFace::OctFace(float rot, float height, bool flip, int subdivLevel) {


	// each sub-divide creates 4 faces from one, thus 4^sub
	faces = pow(4, subdivLevel);

	// note: vertice is a struct declared in OctFace.h; simply makes grouping vertices / allocating memory easier i.e. a1->x; a1->y;
	// we allocate an array for how many faces we have, multiplied by 3 for each vertex of the triangle.
	// this prevents constantly allocating new vertices
	verts = (vertice*) malloc(sizeof(vertice) * (faces * 3));

	this->rot = rot;

	float v1[3], v2[3], v3[3];

	// this generates our base face we will be working off - either up or down facing.
	// if flip, we draw from the highest point, (0, 100, 0)
	// else, we draw from the lowest point, (0,-100,0)
	if (flip) {
		v1[0] = 0;				v1[1] = 0 + height; v1[2] = 0;
		v2[0] = 0,				v2[1] = 0;			v2[2] = 0 - height;
		v3[0] = 0 + -height;	v3[1] = 0;			v3[2] = 0;
	} else {
		v1[0] = 0;				v1[1] = -height;	v1[2] = 0;
		v2[0] = 0 + -height,	v2[1] = 0;			v2[2] = 0;
		v3[0] = 0;				v3[1] = 0;			v3[2] = 0 + -height;
	}


    // subdivide this face, which will store all necessary vertices in our verts array
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

void OctFace::draw() {

	int block = (faces * 3);

	glPushMatrix();
	// modify in actual space
	glMatrixMode(GL_MODELVIEW);

	// we want to rotate around the up axis
	glRotatef(rot, 0.0, 1.0, 0.0);

	// block is simply a synonym for 'face'; we just want 3 vertices at a time
	for (int i = 0; i < block; i += 3) {

		vertice a1 = verts[i], 
				a2 = verts[i + 1], 
				a3 = verts[i + 2];

		// draw our actual solid face
		glColor3d(255, 0, 0);
		glBegin(GL_TRIANGLES);
			glVertex3f(a1.x, a1.y, a1.z);
			glVertex3f(a2.x, a2.y, a2.z);
			glVertex3f(a3.x, a3.y, a3.z);
		glEnd();

		// draw our wireframe
		glColor3d(0, 0, 0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(a1.x, a1.y, a1.z);
			glVertex3f(a2.x, a2.y, a2.z);
			glVertex3f(a3.x, a3.y, a3.z);
		glEnd();
	}




	// return to projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

void OctFace::subdivide(float a[], float b[], float c[], int level)
{
    // once we've hit 0, we can store our vertices.
	if (level == 0) {
		vertice a1, a2, a3;
	
		a1.x = a[0]; a1.y = a[1]; a1.z = a[2];
		a2.x = b[0]; a2.y = b[1]; a2.z = b[2];
		a3.x = c[0]; a3.y = c[1]; a3.z = c[2];

		// vcount keeps track of where we are in the array; declared in the header OctFace.h
		verts[vcount++] = a1;
		verts[vcount++] = a2;
		verts[vcount++] = a3;

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

	// subdivide the triangle from midpoints (as above, t1-3)
    subdivide(t2, t3, t1, level - 1);

    // subdivide the triangles outside of the midpoints
    subdivide(c, t3, t2, level - 1);
    subdivide(t2, t1, b, level - 1);
    subdivide(t3, a, t1, level - 1);
}
