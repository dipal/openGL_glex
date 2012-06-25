#include "background.h"

background::background(point ipos) : pos(ipos)
{
}


void background::init(){}
void background::animate(){}

void background::pilar()
{
    glRotatef(45,0,0,1);
    gluCylinder(gluNewQuadric(),40,40,100,4,4);
}

void background::draw()
{
    glPushMatrix();{
        glTranslatef(pos.x,pos.y,pos.z);

        //plane
        glColor3f(.2,.5,0);
        glBegin(GL_QUADS);{
            glVertex3f(-1000,-1000,0);
            glVertex3f( 1000,-1000,0);
            glVertex3f( 1000, 1000,0);
            glVertex3f(-1000, 1000,0);
        }glEnd();

        glColor3f(1,1,.5);
        glPushMatrix();{
            glTranslatef(0,-300,0);
            pilar();
        }glPopMatrix();

        glPushMatrix();{
            glTranslatef(0,300,0);
            pilar();
        }glPopMatrix();

        //glColor3f(.5,.5,.5);

    }glPopMatrix();
}
void background::keyboardListener(unsigned char key, int x,int y){}
void background::specialKeyListener(int key, int x,int y){}
void background::mouseListener(int button, int state, int x, int y){}
