#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glut.h>
#include <vector>
#include <math.h>

#include "point.h"
#include "angle.h"

using namespace std;

class project
{
public:
    project();


    double cameraAngle;			//in radian
    double cameraAngleDelta;

    double cameraHeight;
    double cameraRadius;

    int moveSpeed;
    int rotateSpeed;

    point pos;
    point look;
    point headDir;

    angle ang;

    double rectAngle;	//in degree

    bool canDrawGrid;


    void moveXAxis(bool dir);
    void moveYAxis(bool dir);
    void moveZAxis(bool dir);
    void rotateXAxis(bool dir);
    void rotateYAxis(bool dir);
    void rotateZAxis(bool dir);

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);

};

#endif // PROJECT_H
