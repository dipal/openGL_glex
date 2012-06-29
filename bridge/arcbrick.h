//============================================================================
// Name        : arcbrick.h
// Author      : enzam
// Created At  : Jun 29, 2012 11:18:16 AM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef ARCBRICK_H_
#define ARCBRICK_H_

#include "shapeinterface.h"

class ArcBrick: public ShapeInterface {
	double xLen, yLen, zLen;
	int numSteps;
	GLuint textureId;
	double xRepeat, yRepeat;
public:
	ArcBrick(double xLen, double yLen, double zLen, int numSteps,
			GLuint textureId, double xRepeat, double yRepeat);

	void draw();
};

#endif /* ARCBRICK_H_ */
