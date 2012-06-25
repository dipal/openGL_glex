#ifndef SHAPEINTERFACE_H
#define SHAPEINTERFACE_H

class ShapeInterface
{
public:
    ShapeInterface();

    virtual void init() {}
    virtual void animate() {}
    virtual void draw() {}
    virtual void keyboardListener(unsigned char key, int x,int y) {}
    virtual void specialKeyListener(int key, int x,int y) {}
    virtual void mouseListener(int button, int state, int x, int y) {}
};

#endif // SHAPEINTERFACE_H
