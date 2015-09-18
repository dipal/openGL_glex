#ifndef POSITION_H
#define POSITION_H

class position
{
public:
    position();
    position(int iX,int iY,int iZ=0);
    void setX(int);
    void setY(int);
    void setZ(int);

    int getX();
    int getY();
    int getZ();

    int x;
    int y;
    int z;
};

#endif // POSITION_H
