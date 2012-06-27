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
    double roadLength;
    double bridgeWidth;
    double pilarLength;
    double plilarHeight;

    void pilar();
    void archUp();
    void archDown();
    void road();
    void dbox(double xWidth,double yWidth,double zWidth,double xWidthTop=0);

    void drawPlane();
    void drawObjects();

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);
};

#endif // BACKGROUND_H
