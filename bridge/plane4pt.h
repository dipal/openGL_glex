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
#include "point.h"

#include <GL/gl.h>

class Plane4Pt: public ShapeInterface {
	GLuint textureId;
	double xRepeat, yRepeat;
	vector<point> pts;
public:
        Plane4Pt(point pt1, point pt2, point pt3, point pt4, GLuint textureId=0,
                        double xRepeat=1, double yRepeat=1);

	void draw();
};

#endif /* PLANE4PT_H_ */
