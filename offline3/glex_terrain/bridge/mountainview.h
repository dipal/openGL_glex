#ifndef MOUNTAINVIEW_H
#define MOUNTAINVIEW_H

#include <vector>

#include <shapeinterface.h>
#include <GL/glut.h>

#include <point.h>
#include <terrain.h>

using namespace std;

class MountainView : public ShapeInterface
{
    Terrain *mountain;
    vector<vector<Terrain*> > water;
    string resourcePath;
    double waterUpDir;
public:
    MountainView();
    void init();
    void draw();
    void animate();
    void keyboardListener(unsigned char key);

    void drawTerrain(Terrain *terrain,point color=point(0,1,0));
};

#endif // MOUNTAINVIEW_H
