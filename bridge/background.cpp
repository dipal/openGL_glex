#include "background.h"

background::background(point ipos) : pos(ipos)
{
}


void background::init()
{
    bridgeLength=600;
}
void background::animate(){}

void background::pilar()
{
    glRotatef(45,0,0,1);
    gluCylinder(gluNewQuadric(),40,40,170,4,4);
}

void archDown()
{
    glRotatef(90,0,1,0);
    glutSolidTorus(5,350,100,100);
}


void archUp()
{
    double theta=0;
    double circleTheta=0;
    double pi=M_PI;


    glScalef(1,100,3);
    {
        for (circleTheta=0; circleTheta<=2.0*pi; circleTheta+=0.01) {
            //glVertex3f(10*cos(circleTheta),0,1/3.0*sin(circleTheta));
            glPushMatrix();{
                glTranslatef(5.0*cos(circleTheta),0,5*1/3.0*sin(circleTheta));
                glBegin(GL_LINE_STRIP); {
                    for (theta=-pi; theta<=pi; theta+=0.05) {
                        double numc=M_2_PI/0.01;
                        double numt=M_2_PI/0.01;
                        double t=circleTheta;
                        double s=theta;
                        double x = cos(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
                        double z = sin(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
                        double y = sin(s*M_2_PI/numc);
                        glNormal3f(x,y,z);
                        glVertex3f(0,theta,20*cos(theta));
                    }
                }
                glEnd();
            }glPopMatrix();
        }
    }

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

        //left pilar
        glColor3f(1,1,.5);
        glPushMatrix();{
            glTranslatef(0,-bridgeLength/2,0);
            pilar();
        }glPopMatrix();

        //right pilar
        glPushMatrix();{
            glTranslatef(0,bridgeLength/2,0);
            pilar();
        }glPopMatrix();

        //arch down side1
        glPushMatrix();{
            glTranslatef(20,0,-200);
            //archDown();
        }glPopMatrix();

        //arch down side2
        glPushMatrix();{
            glTranslatef(-20,0,-200);
            //archDown();
        }glPopMatrix();

        //arch up side1
        glPushMatrix();{
            glTranslatef(20,0,200);
            archUp();
        }glPopMatrix();

        //arch up side1
        glPushMatrix();{
            glTranslatef(-20,0,200);
            archUp();
        }glPopMatrix();

        glPushMatrix();{
            glTranslatef(0,0,80);
            glScalef(1,125,5.5);
            double theta=0;
            double pi=M_PI;
            //glTranslatef(0,-pi/2.0,0);//pi/3.0-pi/3.0-pi/2.0
            glBegin(GL_LINE_STRIP); {
                for (theta=-pi; theta<=pi; theta+=0.01) {
                    glVertex3f(0,theta,20*cos(theta));
                }
            }
            glEnd();
        }glPopMatrix();
        //glColor3f(.5,.5,.5);

    }glPopMatrix();
}
void background::keyboardListener(unsigned char key, int x,int y){}
void background::specialKeyListener(int key, int x,int y){}
void background::mouseListener(int button, int state, int x, int y){}
