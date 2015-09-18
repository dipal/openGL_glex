#include "solar.h"

solar::solar()
{
}


void solar::init() {
    cameraAngle = 0;	//// init the cameraAngle
    cameraAngleDelta = 0.01;
    rectAngle = 0;
    canDrawGrid = true;
    cameraHeight = 150;
    cameraRadius = 150;
    R1=40;
    r1=32;
    r1angle=0;
    mr1angle=0;
    mr2angle=0;
    R2=12;

}

void solar::animate() {
    //cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!
    r1angle+=0.02;
    mangle+=1;
    mr1angle+=1.5;
    mr2angle+=1.5;
    r2angle+=0.05;
    //codes for any changes in Models

    //rectAngle -= 1;

}

void solar::draw() {
    gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(70,70,70,		0,0,0,		0,0,1);    //NOTE: the camera still CONSTANTLY looks at the center
    // cameraAngle is in RADIAN, since you are using inside COS and SIN


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects
    //rotate this rectangle around the Z axis


    glPushMatrix();{

        glTranslatef(R1*cos(r1angle),r1*sin(r1angle),0);

        glPushMatrix();{
            glColor3f(1,0,0);
            glRotatef(mr1angle,0,0,1);
            glutWireSphere(5, 10, 10);
        } glPopMatrix();

        glPushMatrix();{
            glBegin(GL_LINE_STRIP);
            double theta=0;
            double pi=3.14159;
            for (theta=0;theta<=2*pi+1; theta+=0.1) {
                glVertex3f(R2*cos(theta),R2*sin(theta),0);
            }
            glEnd();
        }glPopMatrix();

        glPushMatrix();{
            glTranslatef(R2*cos(r2angle),R2*sin(r2angle),0);
            glColor3f(1,0,0);
            glRotatef(mr2angle,0,0,1);
            glutWireSphere(3,10,10);
        }glPopMatrix();
    }glPopMatrix();


    glPushMatrix();{
        glBegin(GL_LINE_STRIP);
        double theta=0;
        double pi=3.14159;
        for (theta=0;theta<=2*pi+1; theta+=0.1) {
            glVertex3f(R1*cos(theta),r1*sin(theta),0);
        }
        glEnd();
    }glPopMatrix();


    glPushMatrix();{
        glColor3f(0,0,1);
        glRotatef(mangle,0,0,1);
        glutWireSphere(10, 10, 10);
    }glPopMatrix();

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


    //////// ------ NOTE ---- ORDER matters. compare last two spheres!

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)

}

void solar::keyboardListener(unsigned char key, int x,int y) {
    switch(key){

    case '1':	//reverse the rotation of camera
        cameraAngleDelta = -cameraAngleDelta;
        break;

    case '2':	//increase rotation of camera by 10%
        cameraAngleDelta *= 1.1;
        break;

    case '3':	//decrease rotation
        cameraAngleDelta /= 1.1;
        break;

    case '8':	//toggle grids
        canDrawGrid = 1 - canDrawGrid;
        break;

    case 27:	//ESCAPE KEY -- simply exit
        exit(0);
        break;

    default:
        break;
    }

}

void solar::specialKeyListener(int key, int x,int y) {
    switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
        cameraRadius += 10;
        break;
    case GLUT_KEY_UP:		// up arrow key
        if(cameraRadius > 10)
            cameraRadius -= 10;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += cameraAngleDelta;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= cameraAngleDelta;
        break;

    case GLUT_KEY_PAGE_UP:
        cameraHeight += 10;
        break;
    case GLUT_KEY_PAGE_DOWN:
        cameraHeight -= 10;
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}

void solar::mouseListener(int button, int state, int x, int y) {
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
            cameraAngleDelta = -cameraAngleDelta;
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
