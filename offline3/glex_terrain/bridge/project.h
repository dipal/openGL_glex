#ifndef PROJECT_H
#define PROJECT_H

#include <GL/glut.h>
#include <vector>
#include <math.h>

#include "point.h"
#include "angle.h"
#include "multishape.h"

#include "background.h"
#include "mountainview.h"
#include "light.h"

using namespace std;

class project
{
public:
    project();

    Light light;
    MultiShape shapes;

    bool isPressed[256];

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void keyboardReleaseListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);
    void motionListener(int x, int y);

};

#endif // PROJECT_H
