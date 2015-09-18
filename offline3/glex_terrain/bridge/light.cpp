//============================================================================
// Name        : light.cpp
// Author      : enzam
// Created At  : Jun 29, 2012 7:40:29 PM
// Description : None
// Accepted	   : Unknown
//============================================================================

#include "light.h"
#include <memory.h>

Light::Light() {
	// TODO Auto-generated constructor stub
}



void Light::init() {
    //setDay();
    //return;
	glEnable(GL_LIGHTING); //Enable lighting
//        glEnable(GL_LIGHT0); //Enable light #0
        glEnable(GL_LIGHT1); //Enable light #1

        setDay();

        GLfloat dayLightColor0Data[] = { 0.8f, 0.8f, 0.9f, 1.0f };
        GLfloat dayLightColor1Data[] = { 0.4f, 0.4f, 1.0f, 1.0f };
        GLfloat dayAmbColorData[] = { 0.5f, 0.5f, 0.9f, 1.0f };
        memcpy(dayLightColor0, dayLightColor0Data, 4 * sizeof(GLfloat));
        memcpy(dayLightColor1, dayLightColor1Data, 4 * sizeof(GLfloat));
        memcpy(dayAmbColor, dayAmbColorData, 4 * sizeof(GLfloat));

        GLfloat nightLightColor0Data[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat nightLightColor1Data[] = { 0.2f, 0.2f, 1.0f, 1.0f };
        GLfloat nightAmbColorData[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        memcpy(nightLightColor0, nightLightColor0Data, 4 * sizeof(GLfloat));
        memcpy(nightLightColor1, nightLightColor1Data, 4 * sizeof(GLfloat));
        memcpy(nightAmbColor, nightAmbColorData, 4 * sizeof(GLfloat));


        memcpy(lightColor0, nightLightColor0, 4 * sizeof(GLfloat));
        memcpy(lightColor1, nightLightColor1, 4 * sizeof(GLfloat));
        memcpy(ambColor, nightAmbColor, 4 * sizeof(GLfloat));

        nStep = 50;
        nowStep = 0;
        sign = 1;

}

#include <iostream>
        using namespace std;

void Light::draw() {
    for(int i = 0; i < 4; i++) {
        double lc0change = (dayLightColor0[i] - nightLightColor0[i]) / nStep;
        lightColor0[i] += lc0change * sign;

        double lc1change = (dayLightColor1[i] - nightLightColor1[i]) / nStep;
        lightColor1[i] += lc1change * sign;

        double ambchange = (dayAmbColor[i] - nightAmbColor[i]) / nStep;
        ambColor[i] += ambchange * sign;

        //        cout << lightColor0[i] << "  ";
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);

//    cout << "DSF " << endl;

    nowStep += sign;
    if(nowStep < 0 || nowStep > nStep) sign *= -1;

    glClearColor(.7 * nowStep / double(nStep), .7 * nowStep / double(nStep), nowStep / double(nStep), 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void Light::setDay() {
    GLfloat lightPos0[] = { 4.0f, 0.0f, 400.0f, 1.0f }; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    GLfloat lightPos1[] = { -100.0f, 900.f, 900.5f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

void Light::setNight()
{
    GLfloat lightPos0[] = { 4.0f, 0.0f, 400.0f, 1.0f }; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}

void Light::keyboardListener(unsigned char key) {
    if (key=='l') setDay();
    if (key=='k') setNight();
}
