#include "multishape.h"
#include <algorithm>

MultiShape::MultiShape()
{
}

void MultiShape::addShape(ShapeInterface* shape) {
    shapes.push_back(shape);
}

void MultiShape::init(){
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->init();
}

void MultiShape::animate(){
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->animate();
}

void MultiShape::keyboardListener(unsigned char key, int x,int y){
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->keyboardListener(key,x,y);
}

void MultiShape::specialKeyListener(int key, int x,int y){
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->specialKeyListener(key,x,y);
}

void MultiShape::mouseListener(int button, int state, int x, int y){
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->mouseListener(button,state,x,y);
}

void MultiShape::draw() {
    for(size_t i = 0; i < shapes.size(); i++) shapes[i]->draw();
}
