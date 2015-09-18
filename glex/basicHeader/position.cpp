#include "position.h"

position::position()
{
    x = y = z = 0;
}

position::position(int iX, int iY, int iZ) : x(iX),y(iY),z(iZ) {

}


void position::setX(int iX) {
    x = iX;
}

void position::setY(int iY) {
    y = iY;
}

void position::setZ(int iZ) {
    z = iZ;
}

int position::getX() {
    return x;
}

int position::getY() {
    return y;
}

int position::getZ() {
    return z;
}
