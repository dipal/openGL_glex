//============================================================================
// Name        : light.cpp
// Author      : enzam
// Created At  : Jun 29, 2012 7:40:29 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#include "light.h"
#include <GL/gl.h>
Light::Light() {
	// TODO Auto-generated constructor stub
}

void Light::init() {
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1

	//    glTranslatef(0.0f, 0.0f, -8.0f);

	//Add ambient light
	GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = { 0.2f, 0.2f, 1.0f, 1.0f }; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	//    //Add directed light
	//    GLfloat lightColor2[] = {0.5f, 0.0f, 0.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//    //Coming from the direction (-1, 0.5, 0.5)
	//    GLfloat lightPos2[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	//    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	//    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

void Light::draw() {
}
