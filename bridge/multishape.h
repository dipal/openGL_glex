#ifndef MULTISHAPE_H
#define MULTISHAPE_H

#include "shapeinterface.h"
#include <vector>

using namespace std;

class MultiShape : public ShapeInterface
{
    vector<ShapeInterface*> shapes;
public:
    MultiShape();
    void addShape(ShapeInterface* shape) ;

    void init();
    void animate();
    void draw();
    void keyboardListener(unsigned char key);
    void specialKeyListener(int key);
    void mouseListener(int button, int state, int x, int y);

};

#endif // MULTISHAPE_H
