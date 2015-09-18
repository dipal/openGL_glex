#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <math.h>
#include <iostream>
#include <GL/glut.h>

#include "shape.h"
#include "point.h"
#include "angle.h"

using namespace std;

class spaceCraft
{
public:
    spaceCraft();
    spaceCraft(point ipos,angle iang=angle(0,0,0));

    point pos;

    angle ang;

    int rotateSpeed;

    point front;
    point up;
    point right;

    void circle(double radius,angle iang=angle(0,0,0),point p=point(0,0,0));
    void wing();

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);

};


#endif // SPACECRAFT_H
