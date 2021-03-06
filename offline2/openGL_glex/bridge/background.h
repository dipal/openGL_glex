#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>

#include "point.h"
#include "shapeinterface.h"
#include "imageloader.h"
#include "plane4pt.h"
#include "string"
#include "arcbrick.h"

class background : public ShapeInterface
{
public:

    background(point ipos=point(0,0,0));

    int LEFT;
    int RIGHT;

    point pos;
    double bridgeLength;
    double roadLength;
    double roadWidth;
    double bridgeWidth;
    double pilarLength;
    double pilarMidHeight;
    double upperPillarWidth;
    double upperPillarHeight;
    double upperSmallPillarLength;
    double upperSmallPillarWidth;
    double upperSmallPillarHeight;
    double pilarTopHeight;

    string resourcePath;

    void pilar();
    void upperPillar(int side);
    void upperPillarUpperPortion(int i);
    void arch(double height=30,double depth=10);
    void bridgeRod();
    void archRodTopDown(double height,int sLimit,int eLimit);
    void archRod();
    void archUp();
    void archDown();
    void road();
    void dbox(double xWidth,double yWidth,double zWidth,double xTopWidth=0,double yTopWidth=0,GLuint textureId=0,double xRepeat=1,double yRepeat=1,point upperTranslate=point(0,0,0));
    void wallBrick(double width,double height,double depth,GLuint textureId=0,double xRepeat=1,double yRepeat=1);
    void wall(double width,double height,double depth,int nstep=1,GLuint textureId=0,bool isDesigned=1,double xRepeat=1,double yRepeat=1);
    void widthedTriangle(double xWidth,double yWidth,double zWidth,double xTopWidth=0,GLuint textureId=0,double xRepeat=1,double yRepeat=1);

    GLuint brickId;
    GLuint rockBrickId;
    GLuint redBrickId;
    GLuint whiteBrickId;
    GLuint railTrackId;
    GLuint rockRoadId;
    GLuint railTrackShinyId;
    GLuint wallId;
    GLuint ironId;
    GLuint waterId;
    GLuint skyFrontId;
    GLuint skyBackId;
    GLuint skyLeftId;
    GLuint skyRightId;
    GLuint skyTopId;

    bool highQlty;

    vector<Plane4Pt> waterSurfaces;

    void drawPlane();
    void drawObjects();

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);
};

#endif // BACKGROUND_H
