#ifndef SIZE_H
#define SIZE_H

class size
{
private:

public:
    size();
    size(int iWidth, int iHeight);
    int getWidth();
    int getHeight();

    void setWidth(int);
    void setHeight(int);

    int width;
    int height;
};

#endif // SIZE_H
