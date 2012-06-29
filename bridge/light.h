//============================================================================
// Name        : light.h
// Author      : enzam
// Created At  : Jun 29, 2012 7:40:29 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#ifndef LIGHT_H_
#define LIGHT_H_

#include "shapeinterface.h"

class Light: public ShapeInterface {
public:
	Light();
	void init();
	void draw();
};

#endif /* LIGHT_H_ */
