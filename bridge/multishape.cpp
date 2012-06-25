#include "multishape.h"

MultiShape::MultiShape()
{
}

void MultiShape::addShape(ShapeInterface* shape) {
    shapes.push_back(shape);
}
