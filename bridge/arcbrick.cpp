//============================================================================
// Name        : arcbrick.cpp
// Author      : enzam
// Created At  : Jun 29, 2012 11:18:16 AM
// Description : None
// Accepted	   : Unknown
//============================================================================

#include "arcbrick.h"
#include "plane4pt.h"

ArcBrick::ArcBrick(double xLen, double yLen, double zLen, int numSteps,
		GLuint textureId, double xRepeat, double yRepeat) :
		xLen(xLen), yLen(yLen), zLen(zLen), numSteps(numSteps), textureId(
				textureId), xRepeat(xRepeat), yRepeat(yRepeat) {
}

void ArcBrick::draw() {
	//left
	Plane4Pt(point(-xLen, 0, 0), point(-xLen, yLen, 0),
			point(-xLen, yLen, zLen), point(-xLen, 0, zLen), textureId, xRepeat,
			yRepeat).draw();

	//top
	Plane4Pt(point(-xLen, 0, zLen), point(-xLen, yLen, zLen),
			point(0, yLen, zLen), point(0, 0, zLen), textureId, xRepeat,
			yRepeat).draw();

	double step = M_PI_2 / numSteps;

	double prex = -xLen, prez = 0;
        for (double theta = M_PI - step; theta >= M_PI_2; theta -= step) {
		double x = xLen * cos(theta);
		double z = zLen * sin(theta);

		//front triangle
                Plane4Pt(point(prex, 0, prez), point(x, 0, z), point(x, 0, z),
                                point(-xLen, 0, zLen), textureId, xRepeat, yRepeat).draw();

		//back triangle
                Plane4Pt(point(prex, yLen, prez), point(x, yLen, z), point(x, yLen, z),
                                point(-xLen, yLen, zLen), textureId, xRepeat, yRepeat).draw();

		//down rectangle
		Plane4Pt(point(prex, 0, prez), point(x, 0, z), point(x, yLen, z),
				point(prex, yLen, prez), textureId, xRepeat, yRepeat).draw();


                prex = x; prez = z;
        }

}
