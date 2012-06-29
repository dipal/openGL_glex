#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>

#include "point.h"
#include "shapeinterface.h"
#include "imageloader.h"
#include "plane4pt.h"
#include "string"

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
    double upperPillarWidth;

    string resourcePath;

    void pilar();
    void upperPillar();
    void archUp();
    void archDown();
    void road();
    void dbox(double xWidth,double yWidth,double zWidth,double xTopWidth=0,double yTopWidth=0,GLuint textureId=0,double xRepeat=1,double yRepeat=1);


    GLuint brickId;
    GLuint rockBrickId;
    GLuint redBrickId;
    GLuint whiteBrickId;

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
