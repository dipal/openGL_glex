#include "size.h"

size::size()
{
    height = width = 400;
}

size::size(int iWidth, int iHeight) : width(iWidth),height(iHeight) {

}

int size::getHeight() {
    return height;
}

int size::getWidth() {
    return width;
}

void size::setHeight(int h) {
    height = h;
}

void size::setWidth(int w) {
    width = w;
}

