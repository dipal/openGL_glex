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
#include <GL/gl.h>

class Light: public ShapeInterface {
    GLfloat dayLightColor0[4];
    GLfloat dayLightColor1[4];
    GLfloat dayAmbColor[4];

    GLfloat nightLightColor0[4];
    GLfloat nightLightColor1[4];
    GLfloat nightAmbColor[4];

    GLfloat lightColor0[4];
    GLfloat lightColor1[4];
    GLfloat ambColor[4];


    int nStep, nowStep;
    int sign;

public:
	Light();
	void init();
	void draw();
        void setDay();
        void setNight();
        void keyboardListener(unsigned char key);
};

#endif /* LIGHT_H_ */
