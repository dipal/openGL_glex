#include "glex.h"


glex::glex()
{
}


project model;

void enlighten(GLenum light,GLfloat color[], GLfloat pos[]) {
    glLightfv(light, GL_DIFFUSE, color);
    glLightfv(light, GL_POSITION, pos);
}


void projectInit() {
    model.init();
}

void initRendering() {

    projectInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    glShadeModel(GL_SMOOTH); //Enable smooth shading

    glClearColor(0,0,0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70,	1,	0.1,	10000.0);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0,0,0, 0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    /**
      All Shape Drawings
    **/
    model.draw();

    glutSwapBuffers();
}

void animate() {
    model.animate();

    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x,int y){
    model.keyboardListener(key,x,y);
}

void specialKeyListener(int key, int x,int y){
    model.specialKeyListener(key,x,y);
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
    model.mouseListener(button,state,x,y);
}

void init(int       argc,
          char      **argv,
          uint      displayMode,
          point     initPos,
          QSize      initSize,
          string    windowTitle
          )
{
    glutInit(&argc, argv);
    //Simple buffer
    glutInitDisplayMode(displayMode);
    glutInitWindowPosition(initPos.x,initPos.y);
    glutInitWindowSize(initSize.height(),initSize.width());
    glutCreateWindow(windowTitle.c_str());
    initRendering();

    glutDisplayFunc(draw);
    glutIdleFunc(animate);

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);


    glutMouseFunc(mouseListener);

    //Call to the drawing function


}

void run() {
    glutMainLoop();
}
