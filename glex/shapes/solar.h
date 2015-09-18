#ifndef SOLAR_H
#define SOLAR_H
#include <math.h>
#include <GL/glut.h>

class solar
{
public:
    solar();

    double cameraAngle;			//in radian
    double cameraAngleDelta;

    double cameraHeight;
    double cameraRadius;

    double rectAngle;	//in degree

    bool canDrawGrid;

    double R1,r1;
    double R2,r2;
    double r1angle;
    double r2angle;

    double mangle;
    double mr1angle;
    double mr2angle;

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);

};

#endif // SOLAR_H
