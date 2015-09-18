#include "spacecraft.h"

#define COLOR_RED   1,0,0
#define COLOR_GREEN 0,1,0
#define COLOR_BLUE  0,0,1
#define COLOR_BLACK 0,0,0
#define COLOR_WHITE 1,1,1

//#define TORUS
spaceCraft::spaceCraft()
{
    pos = point(0,0,0);
    ang = angle(0,0,0);

    front = point(0,1,0);
    rotateSpeed=10;
}

spaceCraft::spaceCraft(point ipos,angle iang) : pos(ipos),ang(iang) {
    front = point(1,0,0);
    right = point(0,1,0);
    up = point(0,0,1);
    rotateSpeed=10;
}

void spaceCraft::init() {

    //glutIgnoreKeyRepeat(1);
}

void spaceCraft::animate() {


}

void spaceCraft::wing() {
    int slices=100,stacks=100;
    gluCylinder(gluNewQuadric(),3,4,50,slices,stacks);
    glPushMatrix();{
        //back
        glColor3f(COLOR_RED);
        gluDisk(gluNewQuadric(),0,3,slices,stacks);
        glColor3f(COLOR_WHITE);

        gluSphere(gluNewQuadric(),2,100,100);

        //mid
        glPushMatrix();{
            glTranslatef(0,0,40);
            gluSphere(gluNewQuadric(),4,slices,stacks);
        }glPopMatrix();

        //front
        glPushMatrix();{
            glTranslatef(0,0,50);
            gluDisk(gluNewQuadric(),0,4,slices,stacks);
            glColor3f(COLOR_RED);
            gluSphere(gluNewQuadric(),3,slices,stacks);
            glColor3f(COLOR_WHITE);
        }glPopMatrix();

    }glPopMatrix();
}

void spaceCraft::circle(double radius,angle iang,point p) {
    glPushMatrix(); {
        glTranslatef(p.x,p.y,p.z);

        glRotatef(iang.x,1,0,0);
        glRotatef(iang.y,0,1,0);
        glRotatef(iang.z,0,0,1);

        glBegin(GL_TRIANGLE_FAN);{
            double pi=3.14159;
            for (double theta=0;theta<=2*pi+1; theta+=0.1) {
                glVertex3f(radius*cos(theta),radius*sin(theta),0);
            }
        }glEnd();
    } glPopMatrix();
}


void wingBar(bool boolType) {
    int dir=1;
    if (boolType) dir*=-1;
    double r2=4;
    double r1=2;
    glPushMatrix();{
        glRotatef(90,0,1,0);
        double theta;
        double pi=2.0*acos(0.0);
        for (theta=0; theta<=2*pi+1;theta+=0.01) {
            glBegin(GL_LINES);{
                glVertex3f(-35+r2*cos(theta),r1*sin(theta),0);
                glVertex3f(r2*cos(theta),dir*40+r1*sin(theta),30);
            }glEnd();
        }
    } glPopMatrix();
}

void spaceCraft::draw() {


    glPushMatrix();{
        glBegin(GL_LINES);{
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(front.x*100,front.y*100,front.z*100);
            //glVertex3f(100,000,000);

            glColor3f(0,1,0);
            glVertex3f(0,0,0);
            glVertex3f(right.x*100,right.y*100,right.z*100);

            glColor3f(0,0,1);
            glVertex3f(0,0,0);
            glVertex3f(up.x*100,up.y*100,up.z*100);
        }glEnd();

        glColor3f(1,1,1);
        glTranslatef(pos.x,pos.y,pos.z);
        glRotatef(ang.x,1,0,0);
        glRotatef(ang.y,0,1,0);
        glRotatef(ang.z,0,0,1);


        glColor3f(1,1,1);
        //glutSolidTeapot(10);
#ifdef TORUS
        GLdouble slices = 100,stacks = 100;
        GLdouble radius = 10;
        gluCylinder(gluNewQuadric(), 10,5,40, slices, stacks );
        //gluSphere( gluNewQuadric(), radius , slices , stacks  );
        glPushMatrix();{
            glRotatef(-90,1,0,0);
            //gluCylinder(gluNewQuadric(),5,7,20,100,100);
        }glPopMatrix();
        glutWireTorus( 10, 20, 100, 3);
#else
        GLdouble slices = 100,stacks = 100;
        GLdouble radius = 10;
        glRotatef(-90,0,1,0);

        double baseLength=80;
        gluCylinder(gluNewQuadric(), 7,10,baseLength, slices, stacks );
        gluDisk(gluNewQuadric(),0,7,slices,stacks);

        glPushMatrix();{
            glTranslatef(2.8,0,-15);
            glRotatef(-10,0,1,0);
            gluCylinder(gluNewQuadric(),5,7,16,slices,stacks);
            gluDisk(gluNewQuadric(),0,5,slices,stacks);
        }glPopMatrix();

        /** LEFT WING **/
        glColor3f(COLOR_WHITE);
        glPushMatrix();{
            wingBar(0);
            glTranslatef(30,40,-30);
            wing();
        }glPopMatrix();

        /** RIGHT WING **/
        glColor3f(COLOR_WHITE);
        glPushMatrix();{
            wingBar(1);
            glTranslatef(30,-40,-30);
            wing();
        }glPopMatrix();

        int i;
        //cock
        double cockPitHeigt=35;
        double cockPitDist=-100;
        glPushMatrix();{
            glRotatef(90,0,1,0);
            glTranslated(cockPitDist,0,cockPitHeigt);
            gluCylinder(gluNewQuadric(),35,40,10,slices,stacks);
            //updisk
            glPushMatrix();{
                glTranslatef(0,0,10);
                gluDisk(gluNewQuadric(),0,40,slices,stacks);
            }glPopMatrix();
            glPushMatrix();{
                glTranslatef(0,0,8);
                glutSolidSphere(8,slices,stacks);

                glTranslatef(0,0,8);
                glutSolidSphere(2,slices,stacks);
            }glPopMatrix();
            //downdisk
            gluDisk(gluNewQuadric(),0,35,slices,stacks);
        } glPopMatrix();

        //cockbar
        double rUp1=13;
        double rUp2=4;

        double rDown1=4;
        double rDown2=8;
        glPushMatrix();{
            glRotatef(90,0,1,0);
            double theta;
            double pi=2.0*acos(0.0);
            for (theta=0; theta<=2*pi+1;theta+=0.01) {
                glBegin(GL_LINES);{
                    glVertex3f(-50+rDown1*cos(theta),rDown1*sin(theta),0);
                    glVertex3f(cockPitDist+10+rUp1*cos(theta),rUp2*sin(theta),cockPitHeigt);
                }glEnd();
            }
        } glPopMatrix();
        //front
        glPushMatrix();{
            glTranslatef(0,0,baseLength);
            gluCylinder(gluNewQuadric(),10,8,5,slices,stacks );
//            for (int i=0; i<5; i++) {
//                glPushMatrix();{
//                    glTranslatef(0,0,0+i);
//                    gluCylinder(gluNewQuadric(),10-i*0.5,10-i*0.4,1,slices,stacks );
//                }glPopMatrix();
//            }

            //circle(10);
            gluDisk(gluNewQuadric(),0,10,slices,stacks);
            glPushMatrix();{
                glTranslatef(0,0,5);
                gluDisk(gluNewQuadric(),0,8,slices,stacks);
                glColor3f(.2,.2,.2);
                gluCylinder(gluNewQuadric(),1,5,3,slices,stacks);
                gluCylinder(gluNewQuadric(),1,1,8,slices,stacks);
            }glPopMatrix();
        }glPopMatrix();

//        glPushMatrix(); {
//            GLdouble length=20;
//            glTranslatef(0,0,-length);
//            gluCylinder(gluNewQuadric(),5,7,length,slices,stacks);
//        }glPopMatrix();
#endif

    }glPopMatrix();

}

void spaceCraft::keyboardListener(unsigned char key, int x,int y) {
    switch(key){

    case '1':
        break;

    case '3':
        break;

    case 27:
        break;

    case 'a':
        pos = pos-right.unit();
        //front = front-right;
        break;
    case 'd':
        pos = pos+right.unit();
        break;
    case 'w':
        pos = pos - front.unit();
        break;
    case 's':
        pos = pos + front.unit();
        break;
    case 'u':
        pos = pos + up.unit();
        break;
    case 'i':
        pos = pos - up.unit();
        break;
    case '4':
        right = right.rotate(front,10);
        up = up.rotate(front,10);
        ang.x+=10;
        break;
    case '6' :
        right = right.rotate(front,-10);
        up = up.rotate(front,-10);
        ang.x-=10;
        break;
    case '8' :
        front = front.rotate(right,10);
        up = up.rotate(right,10);
        ang.y+=10;
        break;
    case '2' :
        front = front.rotate(right,-10);
        up = up.rotate(right,-10);
        ang.y-=10;
        break;

    case '5' :
        front = front.rotate(up,-10);
        right = right.rotate(up,-10);
        ang.z-=10;
        break;
    case '0' :
        front = front.rotate(up,10);
        right = right.rotate(up,10);
        ang.z+=10;
        break;
    default:
        break;
    }

}

void spaceCraft::specialKeyListener(int key, int x,int y) {
    switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
        break;
    case GLUT_KEY_UP:		// up arrow key
        break;

    case GLUT_KEY_RIGHT:
        break;
    case GLUT_KEY_LEFT:
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
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

void spaceCraft::mouseListener(int button, int state, int x, int y) {
    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
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
