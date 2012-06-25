#ifndef MULTISHAPE_H
#define MULTISHAPE_H

#include "shapeinterface.h"
#include <vector>

class MultiShape : public ShapeInterface
{
    vector<ShapeInterface*> shapes;
public:
    MultiShape();
    void addShape();
    void draw() {
        for(size_t i = 0; i < shapes.size(); i++) shapes[i]->draw();
    }
};

#endif // MULTISHAPE_H
