#ifndef GLEX_H
#define GLEX_H
#include <stdio.h>
#include <iostream>
#include <string>

#include <GL/glut.h>

#include "size.h"
#include "point.h"
#include "project.h"
#include "position.h"
#include <math.h>


using namespace std;

class glex
{
public:
    glex();
};


void draw(void);
void init(int       argc,
          char      **argv,
          uint      displayMode = (GLUT_SINGLE | GLUT_RGB),
          point     initPos = point(0,0),
          size      initSize = size(400,400),
          string    windowTitle = "OpenGL window"
          );
void run();
void initRendering();
void animate();
void enlighten(GLenum light,GLfloat color[], GLfloat pos[]);
void keyboardListener(unsigned char key, int x,int y);
void specialKeyListener(int key, int x,int y);
void mouseListener(int button, int state, int x, int y);
void projectInit();



#endif // GLEX_H
