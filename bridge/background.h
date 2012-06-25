#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>

#include "point.h"
#include "shapeinterface.h"

class background : public ShapeInterface
{
public:

    background(point ipos=point(0,0,0));

    point pos;
    double bridgeLength;

    void pilar();

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);
};

#endif // BACKGROUND_H
