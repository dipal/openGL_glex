#include "glex.h"

//Drawing funciton

//Main program
int main(int argc, char **argv)
{
    init(argc,argv,GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH,point(0,0),QSize(800,800));
    run();

    return 0;
}
