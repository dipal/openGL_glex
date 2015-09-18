#ifndef SHAPE_H
#define SHAPE_H

#include "point.h"

class shape
{
public:
    shape();
    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key, int x,int y);
    void specialKeyListener(int key, int x,int y);
    void mouseListener(int button, int state, int x, int y);
};

#endif // SHAPE_H
