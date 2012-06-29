#include "project.h"
#include "viewer.h"

project::project()
{
    ms(isPressed, 0);

    shapes.addShape(&light);
    shapes.addShape(new Viewer(Vector(200,-350,200), Vector(0,-350,200), Vector(0, 0, 1)));
    shapes.addShape(new background());
}

void project::init() {
    shapes.init();
}

void project::animate() {
	glutPostRedisplay();
}

void project::draw() {
    //gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(0, 100, 50,		0,0,0,		0,0,1);
//    gluLookAt(P(pos),		P(look),		P(headDir));

	FOR(i, 256) {
		if(!isPressed[i]) continue;
		shapes.keyboardListener(i);
	}

    glPushMatrix();{
        //glTranslatef(pos.x,pos.y,pos.z);
        glBegin(GL_LINE);{
            glColor3f(0,1,0);
            glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
            glVertex3f(0,  150, 0);

            //X axis
            glColor3f(1,0,0);
            glVertex3f(-150, 0, 0);
            glVertex3f( 150, 0, 0);

            glColor3f(0,0,1);
            glVertex3f(0, 0, -150);
            glVertex3f(0, 0, 150);
        }glEnd();

    }
    glPopMatrix();

    shapes.draw();
}

void project::keyboardListener(unsigned char key, int x,int y) {
    if (key==27) exit(0);
	isPressed[tolower(key)] = true;
}

void project::keyboardReleaseListener(unsigned char key, int x,int y) {
	isPressed[tolower(key)] = false;
}

void project::specialKeyListener(int key, int x,int y) {
//    shapes.specialKeyListener(key);
}

void project::mouseListener(int button, int state, int x, int y) {

    shapes.mouseListener(button,state,x,y);

    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
//            cameraAngleDelta = -cameraAngleDelta;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}

void project::motionListener(int x, int y) {
	shapes.motionListener(x,y);
}
