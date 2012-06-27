//============================================================================
// Name        : plane4pt.h
// Author      : enzam
// Created At  : Jun 27, 2012 10:06:24 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef PLANE4PT_H_
#define PLANE4PT_H_

#include "shapeinterface.h"
#include "vector.h"

class Plane4Pt : public ShapeInterface {
	vector<Vector> pts;
	Plane4Pt(Vector pt1, Vector pt2, Vector pt3, Vector pt4) {
		pts.push_back(pt1); pts.push_back(pt2);
		pts.push_back(pt3); pts.push_back(pt4);
	}

	void draw() {
		glBegin(GL_QUADS); {
			FOR(i, 4) glVertex3d(V(pts[0]));
		} glEnd();
	}
};

#endif /* PLANE4PT_H_ */
