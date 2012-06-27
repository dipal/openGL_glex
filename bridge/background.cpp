#include "background.h"

background::background(point ipos) : pos(ipos)
{
}


void background::init()
{
    bridgeLength=600;
    roadLength=bridgeLength+400;
    bridgeWidth=80;

    pilarLength=60;

    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void background::animate(){}


//error pron
void background::dbox(double xWidth,double yWidth,double zWidth,double xWidthTop)
{
    if (xWidthTop==0) xWidthTop=xWidth;
    glPushMatrix();{
        glScalef(xWidth,yWidth,zWidth);
        glRotatef(45,0,0,1);
        gluCylinder(gluNewQuadric(),1,xWidthTop/xWidth,1,4,4);
    }glPopMatrix();

}

void background::pilar()
{
    dbox(bridgeWidth/2+20,pilarLength/2+20,20,bridgeWidth/2);
    glTranslatef(0,0,20);
    dbox(bridgeWidth/2,pilarLength/2,20,bridgeWidth/2);
    //dbox(bridgeWidth/2+20,pilarLength/2,20,bridgeWidth/2);

    //glTranslatef(0,0,20);
    //dbox(bridgeWidth/2,pilarLength/2,100,bridgeWidth/2);
}

void background::archDown()
{
    //glRotatef(90,0,1,0);
    //glutSolidTorus(5,350,100,100);
    double theta=0;
    double circleTheta=0;
    double pi=M_PI;


    glScalef(1,125,5.5);


    {
        for (circleTheta=0; circleTheta<=2.0*pi; circleTheta+=0.05) {
            //glVertex3f(10*cos(circleTheta),0,1/3.0*sin(circleTheta));
            glPushMatrix();{
                glTranslatef(5.0*cos(circleTheta),0,5*1/5.5*sin(circleTheta));
                glBegin(GL_LINE_STRIP); {
                    for (theta=-pi/1.2; theta<=pi/1.2; theta+=0.05) {
                        glNormal3f(1,0,0);
                        glVertex3f(0,theta,20*cos(theta));
                    }
                }
                glEnd();
            }glPopMatrix();
        }
    }

}

void background::road()
{
    glScalef(bridgeWidth/2,roadLength,10);
    glutSolidCube(1);
}

void background::archUp()
{
    double theta=0;
    double circleTheta=0;
    double pi=M_PI;


    glScalef(1,100,3);

    {
        for (circleTheta=0; circleTheta<=2.0*pi; circleTheta+=0.05) {
            //glVertex3f(10*cos(circleTheta),0,1/3.0*sin(circleTheta));
            glPushMatrix();{
                glTranslatef(5.0*cos(circleTheta),0,5*1/3.0*sin(circleTheta));
                glBegin(GL_LINE_STRIP); {
                    for (theta=-pi; theta<=pi; theta+=0.05) {
//                        double numc=M_2_PI/0.05;
//                        double numt=M_2_PI/0.05;
//                        double s=circleTheta;
//                        double t=theta;
//                        double x = cos(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
//                        double z = sin(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
//                        double y = sin(s*M_2_PI/numc);
//                        glPushMatrix();{
//                            glScalef(1,1,1);
//                            glNormal3f(x,y,z);
//                        }glPopMatrix();
                        glNormal3f(1,0,0);
                        glVertex3f(0,theta,20*cos(theta));
                    }
                }
                glEnd();
            }glPopMatrix();
        }
    }

}


void background::drawPlane()
{
    //plane
    //glColor3f(.2,.5,0);
    glBegin(GL_QUADS);{
        glNormal3f(0,0,1);
        glVertex3f(-1000,-1000,0);
        glVertex3f( 1000,-1000,0);
        glVertex3f( 1000, 1000,0);
        glVertex3f(-1000, 1000,0);
    }glEnd();

}

void background::drawObjects()
{
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
        //glTranslatef(20,0,-300);
        //archDown();
        glTranslatef(bridgeWidth/4,0,80);
        archDown();
    }glPopMatrix();

    //arch down side2
    glPushMatrix();{
        glTranslatef(-bridgeWidth/4,0,80);
        archDown();
    }glPopMatrix();

    //arch up side1
    glPushMatrix();{
        glTranslatef(bridgeWidth/4,0,200);
        archUp();
    }glPopMatrix();

    //arch up side1
    glPushMatrix();{
        glTranslatef(-bridgeWidth/4,0,200);
        archUp();
    }glPopMatrix();

    //road
    glPushMatrix();{
        glTranslatef(0,0,100);
        road();
    }glPopMatrix();


    glPushMatrix();{
//        GLuint textureId = loadTexture(loadBMP("brk.bmp"));

//        glEnable(GL_TEXTURE_2D);
//        glBindTexture(GL_TEXTURE_2D, textureId);

//        //Bottom
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//        glTranslatef(0,0,100);

//        glBegin(GL_QUADS);{
//            glNormal3f(0,0,1);
//            glTexCoord2f(0.0f, 0.0f);
//            glVertex3f(50,-100,-100);
//            glTexCoord2f(10.0f, 0.0f);
//            glVertex3f(50, 100,-100);
//            glTexCoord2f(10.0f, 10.0f);
//            glVertex3f(50, 100, 100);
//            glTexCoord2f(0.0f, 10.0f);
//            glVertex3f(50,-100, 100);
//        }glEnd();

//        glDisable(GL_TEXTURE_2D);


        glTranslatef(0,-100,100);
        Plane4Pt plane(point(50,-100,-100),
                       point(50, 100,-100),
                       point(50, 100, 100),
                       point(50,-100, 100));
        plane.draw();
    }glPopMatrix();
}

void background::draw()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glPushMatrix();{
        glTranslatef(pos.x,pos.y,pos.z);

        drawObjects();


        glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
        glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
        glDisable(GL_DEPTH_TEST); //Disable depth testing
        glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
        //Make pixels in the stencil buffer be set to 1 when the stencil test passes
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        //Set all of the pixels covered by the floor to be 1 in the stencil buffer
        drawPlane();

        glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
        glEnable(GL_DEPTH_TEST); //Enable depth testing
        //Make the stencil test pass only when the pixel is 1 in the stencil buffer
        glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change


        glPushMatrix();{
            glScalef(1, 1, -1);
            drawObjects();
        }glPopMatrix();

        glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer

        //Blend the floor onto the screen
        glEnable(GL_BLEND);
        glColor4f(1, 1, 1, 0.7f);
        drawPlane();
        glDisable(GL_BLEND);

    }glPopMatrix();
}



void background::keyboardListener(unsigned char key, int x,int y){}
void background::specialKeyListener(int key, int x,int y){}
void background::mouseListener(int button, int state, int x, int y){}
