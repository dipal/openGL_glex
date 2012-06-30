#include "background.h"

background::background(point ipos) : pos(ipos)
{
}


void background::init()
{

    LEFT = -1;
    RIGHT = 1;

    bridgeLength=600;
    roadLength=bridgeLength+400;
    bridgeWidth=180;
    roadWidth=bridgeWidth/2;

    pilarLength=60;
    pilarMidHeight=100;
    upperPillarWidth=bridgeWidth/2-30;
    upperPillarHeight=50;
    upperSmallPillarWidth = upperPillarWidth/2-10;
    upperSmallPillarLength = pilarLength/2-10;
    upperSmallPillarHeight=50;
    pilarTopHeight=25;

    highQlty=false;

    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    resourcePath="./../resource/";

    brickId = loadTexture(loadBMP((resourcePath+"brick5.bmp").c_str()));
    whiteBrickId = loadTexture(loadBMP((resourcePath+"brick9.bmp").c_str()));
    rockBrickId = loadTexture(loadBMP((resourcePath+"brick_texture_1.bmp").c_str()));
    railTrackId = loadTexture(loadBMP((resourcePath+"railTrack.bmp").c_str()));
    rockRoadId = loadTexture(loadBMP((resourcePath+"rockRoad.bmp").c_str()));
    railTrackShinyId = loadTexture(loadBMP((resourcePath+"railTrackShiny.bmp").c_str()));
    wallId = loadTexture(loadBMP((resourcePath+"wall.bmp").c_str()));
    ironId = loadTexture(loadBMP((resourcePath+"red.bmp").c_str()));
    waterId = loadTexture(loadBMP((resourcePath+"w8.bmp").c_str()));
    skyFrontId = loadTexture(loadBMP((resourcePath+"front.bmp").c_str()));
    skyBackId = loadTexture(loadBMP((resourcePath+"back.bmp").c_str()));
    skyLeftId = loadTexture(loadBMP((resourcePath+"left.bmp").c_str()));
    skyRightId = loadTexture(loadBMP((resourcePath+"right.bmp").c_str()));
    skyTopId = loadTexture(loadBMP((resourcePath+"top.bmp").c_str()));

    waterSurfaces.push_back(Plane4Pt(point(-1000,-1000,0),
                                     point( 1000,-1000,0),
                                     point( 1000, 1000,0),
                                     point(-1000, 1000,0),
                                     waterId,5,5));
    waterSurfaces.push_back(Plane4Pt(point(-3000,-1000,0),
                                     point(-1000,-1000,0),
                                     point(-1000, 1000,0),
                                     point(-3000, 1000,0),
                                     waterId,5,5));


}
void background::animate(){
    for (int i=0; i<waterSurfaces.size(); i++) waterSurfaces[i].forward(1000,4000);
}


//error pron
void background::dbox(double xWidth,double yWidth,double zWidth,double xTopWidth,double yTopWidth, GLuint textureId,double xRepeat,double yRepeat,point upperTranslate)
{
    if (xTopWidth==0) xTopWidth=xWidth;
    if (yTopWidth==0) yTopWidth=yWidth;

    double xb=xWidth/2;
    double yb=yWidth/2;
    double zb=0;

    double xt=xTopWidth/2;
    double yt=yTopWidth/2;
    double zt=zWidth;

    point bottom1 = point(xb,-yb,zb);
    point bottom2 = point(xb,yb,zb);
    point bottom3 = point(-xb,yb,zb);
    point bottom4 = point(-xb,-yb,zb);

    point up1 = point(xt,-yt,zt)+upperTranslate;
    point up2 = point(xt,yt,zt)+upperTranslate;
    point up3 = point(-xt,yt,zt)+upperTranslate;
    point up4 = point(-xt,-yt,zt)+upperTranslate;

    Plane4Pt(bottom1,
                   bottom2,
                   up2,
                   up1,
                   textureId,xRepeat,yRepeat).draw();

    Plane4Pt(bottom2,
                     bottom3,
                     up3,
                     up2,
                     textureId,xRepeat,yRepeat).draw();

    Plane4Pt(bottom3,
                     bottom4,
                     up4,
                     up3,
                     textureId,xRepeat,yRepeat).draw();

    Plane4Pt(bottom4,
                     bottom1,
                     up1,
                     up4,
                     textureId,xRepeat,yRepeat).draw();

    Plane4Pt(bottom1,
                     bottom2,
                     bottom3,
                     bottom4,
                     textureId,xRepeat,yRepeat).draw();

    Plane4Pt(up1,
                     up2,
                     up3,
                     up4,
                     textureId,xRepeat,yRepeat).draw();
}

void background::wall(double width, double height, double depth,int nstep,GLuint textureId,bool isDesigned, double xRepeat, double yRepeat)
{

    if (!isDesigned) {
        dbox(depth,width,height,0,0,textureId,xRepeat,yRepeat);
        return ;
    }
    double step=width/nstep;

    //cout<<nstep<<" "<<step<<endl;
    glPushMatrix();{
        glTranslatef(0,-width/2+step/2,0);
        for (int i=0; i<nstep; i++)
        {
            wallBrick(step,height,depth,textureId,xRepeat,yRepeat);
            glTranslatef(0,step,0);
        }
    }glPopMatrix();
}

void background::wallBrick(double width,double height,double depth,GLuint textureId,double xRepeat,double yRepeat)
{
    double s=width/4;
    glPushMatrix();{
        glTranslatef(0,-width/2+s/2,0);
        dbox(depth,s,height,0,0,textureId,xRepeat,yRepeat);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(0,width/2-s/2,0);
        dbox(depth,s,height,0,0,textureId,xRepeat,yRepeat);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(0,0,height-2);
        dbox(depth,2*s,2,0,0,textureId,xRepeat,yRepeat);
    }glPopMatrix();

    height-=2;
    glPushMatrix();{
        glTranslatef(depth/2,0,0);
        glRotatef(90,0,0,1);
        ArcBrick(s,depth,height,5,textureId,xRepeat,yRepeat).draw();
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-depth/2,0,0);
        glRotatef(-90,0,0,1);
        ArcBrick(s,depth,height,5,textureId,xRepeat,yRepeat).draw();
    }glPopMatrix();
}

void background::upperPillarUpperPortion(int i)
{

    int pos[][4] = {{-1,-1},{-1,-1},{1,1},{1,1}};
    int rotate[]={-90,-90,90,90};

    int pos2[][4] = {{-1,1},{1,-1},{-1,1},{1,-1}};
    int rotate2[]={180,0,180,0};
    dbox(upperSmallPillarWidth,upperSmallPillarLength,upperSmallPillarHeight,0,0,whiteBrickId,1,1);

    glPushMatrix();{
        double arcWidth=(pilarLength-upperSmallPillarLength*2)/2;
        double arcHeight=arcWidth+10;
        double arcDepth=upperSmallPillarWidth;

        glTranslatef(pos[i][0]*upperSmallPillarWidth/2,pos[i][1]*upperSmallPillarLength,upperSmallPillarHeight-arcHeight);
        glRotatef(rotate[i],0,0,1);
        ArcBrick(arcWidth,arcDepth,arcHeight,5,rockBrickId).draw();
    }glPopMatrix();

    glPushMatrix();{
        double arcWidth=(upperPillarWidth-upperSmallPillarWidth*2)/2;
        double arcHeight=arcWidth+10;
        double arcDepth=upperSmallPillarLength;

        glTranslatef(pos2[i][0]*(upperSmallPillarWidth/2+arcWidth),pos2[i][1]*upperSmallPillarLength/2,upperSmallPillarHeight-arcHeight);
        glRotatef(rotate2[i],0,0,1);
        ArcBrick(arcWidth,arcDepth,arcHeight,5,rockBrickId).draw();
    }glPopMatrix();

    //ArcBrick(10,100,10,5).draw();
}

void background::upperPillar(int side)
{
    double pos[][2]={{1,1},{-1,1},{1,-1},{-1,-1}};

    dbox(upperPillarWidth,pilarLength,upperPillarHeight,0,0,whiteBrickId,1,1);

    glTranslatef(0,0,upperPillarHeight);
    for (int i=0; i<4; i++)
    {
        glPushMatrix();{
            glTranslatef((upperPillarWidth/2-upperSmallPillarWidth/2)*pos[i][0],(pilarLength/2-upperSmallPillarLength/2)*pos[i][1],0);
            upperPillarUpperPortion(i);
        }glPopMatrix();
    }

    glTranslatef(0,0,upperSmallPillarHeight);
    dbox(upperPillarWidth+5,pilarLength+5,pilarTopHeight,0,0,whiteBrickId,1,.5);

    glTranslatef(0,0,pilarTopHeight);
    glPushMatrix();{
        glTranslatef(0,-pilarLength/2,0);
        if (highQlty) {
            glRotatef(90,0,0,1);
            wall(upperPillarWidth+1,20,1,3,wallId);
        }
        else {
            dbox(upperPillarWidth+1,1,20,0,0,wallId);
        }
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(0,pilarLength/2,0);
        if (highQlty) {
            glRotatef(90,0,0,1);
            wall(upperPillarWidth+1,20,1,3,wallId);
        } else {
            dbox(upperPillarWidth+1,1,20,0,0,wallId);
        }
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(side*(-upperPillarWidth/2),0,0);
        if (highQlty) {
            wall(pilarLength+1,20,1,2,wallId);
        } else {
            glRotatef(90,0,0,1);
            dbox(pilarLength+1,1,20,0,0,wallId);
        }
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-1*side*(-upperPillarWidth/2),pilarLength/2-5,0);
        glRotatef(90,0,0,1);
        dbox(10+1,1,20,0,0,wallId);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-1*side*(-upperPillarWidth/2),-(pilarLength/2-5),0);
        glRotatef(90,0,0,1);
        dbox(10+1,1,20,0,0,wallId);
    }glPopMatrix();
}

void background::pilar()
{
    dbox(bridgeWidth+20,pilarLength+20,20,bridgeWidth,pilarLength,rockBrickId,3,1);

    glTranslatef(0,0,20);
    dbox(bridgeWidth,pilarLength,5,bridgeWidth+5,pilarLength+5,rockBrickId,10,5);

    glTranslatef(0,0,5);
    dbox(bridgeWidth+5,pilarLength+5,5,bridgeWidth,pilarLength,rockBrickId,10,1);

    glTranslatef(0,0,5);
    dbox(bridgeWidth,pilarLength,pilarMidHeight-25,0,0,brickId,2,2);


    glTranslatef(0,0,pilarMidHeight-25);

    glPushMatrix();{
        glTranslatef(bridgeWidth/2-upperPillarWidth/2,0,0);
        upperPillar(LEFT);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-(bridgeWidth/2-upperPillarWidth/2),0,0);
        upperPillar(RIGHT);
    }glPopMatrix();

    glTranslatef(0,0,upperPillarHeight+upperSmallPillarHeight);
    dbox(bridgeWidth-2*upperPillarWidth,pilarLength-10,pilarTopHeight,0,0,whiteBrickId);

    glTranslatef(0,0,pilarTopHeight);
    glPushMatrix();{
        glTranslatef(0,pilarLength/2-10,0);
        if (highQlty) {
            glRotatef(90,0,0,1);
            wall(bridgeWidth-2*upperPillarWidth,20,1,3,wallId);
        } else {
            dbox(bridgeWidth-2*upperPillarWidth,1,20,0,0,wallId);
        }
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(0,-pilarLength/2+10,0);
        if (highQlty) {
            glRotatef(90,0,0,1);
            wall(bridgeWidth-2*upperPillarWidth,20,1,3,wallId);
        } else {
            dbox(bridgeWidth-2*upperPillarWidth,1,20,0,0,wallId);
        }
    }glPopMatrix();

}


void background::road()
{
    double x;
    double y;
    double z;

    double width=roadWidth/2;
    glPushMatrix();{
        glTranslatef(-width/2,0,0);
        x=width/6;
        y=roadLength/2;
        z=7;
        Plane4Pt plane = Plane4Pt(point(-x,-y,z),
                                  point(x,-y,z),
                                  point(x,y,z),
                                  point(-x,y,z),
                                  railTrackShinyId,1,20);
        plane.draw();

    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(width/2,0,0);
        x=width/6;
        y=roadLength/2;
        z=7;
        Plane4Pt plane = Plane4Pt(point(-x,-y,z),
                                  point(x,-y,z),
                                  point(x,y,z),
                                  point(-x,y,z),
                                  railTrackShinyId,1,20);
        plane.draw();

    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(0-3,0,0);
        x=width/6;
        y=roadLength/2;
        z=7;
        Plane4Pt plane = Plane4Pt(point(-x,-y,z),
                                  point(x,-y,z),
                                  point(x,y,z),
                                  point(-x,y,z),
                                  railTrackShinyId,1,20);
        plane.draw();

    }glPopMatrix();

    x=roadWidth/2;
    y=roadLength/2;
    z=6;

    Plane4Pt plane = Plane4Pt(point(-x,-y,z),
                     point(x,-y,z),
                     point(x,y,z),
                     point(-x,y,z),
                     rockRoadId,10,50);
    plane.draw();

    glTranslatef(0,0,-5);
    dbox(bridgeWidth/2,roadLength,10,0,0,ironId,20,1);
    //glScalef(bridgeWidth/2,roadLength,10);
    //glutSolidCube(1);
}

void background::arch(double height,double depth)
{
    double pi=M_PI;
    for (double step=-pi; step<=pi; step+=.05) {
        glPushMatrix();{
            glTranslatef(0,step*50,height*cos(step));
            //glRotatef(-sin(step)*180/pi,1,0,0);
            //glutSolidCube(10);
            double x1=depth/2;
            double y1=step*50;
            double z1=height*cos(step);

            double x2=-depth/2;
            double y2=(step+.1)*50;
            double z2=height*cos(step+.1);


            Plane4Pt planeUpDown = Plane4Pt(point(x1,y1,z1),
                                      point(x1,y2,z2),
                                      point(x2,y2,z2),
                                      point(x2,y1,z1),
                                            ironId);
            Plane4Pt planeLeftWrite = Plane4Pt (point(x1,y1,z1),
                                                point(x1,y1,z1-depth),
                                                point(x1,y2,z2-depth),
                                                point(x1,y2,z2),
                                                ironId);
            planeUpDown.draw();
            planeLeftWrite.draw();

            glTranslatef(0,0,-depth);
            planeUpDown.draw();

            glTranslatef(-depth,0,depth);
            planeLeftWrite.draw();

        }glPopMatrix();
    }
}

void background::archDown()
{
    bridgeRod();
    archRod();
    arch(40,10);
}

void background::archUp()
{
    arch(30,7);
}

void background::archRodTopDown(double height,int sLimit,int eLimit)
{
    double pi=M_PI;
    int i=0;
    for (double step=-pi; step<=pi; step+=.3,i++) {
        glPushMatrix();{
            double cs=cos(step);
            double csp=cos(step+.3);
            glTranslatef(0,100*step,2*height*cs-5);

            if (i>=sLimit && i<=eLimit) {
                glRotatef(-90,0,1,0);
                dbox(4,4,bridgeWidth/2,0,0,ironId,1,20);

                int transDir=-1;
                if (step<0) transDir=1;
                dbox(4,4,bridgeWidth/2,0,0,ironId,1,20,point(transDir*2*height*(csp-cs)+transDir*2,transDir*100*0.3,0));

                glTranslatef(0,0,bridgeWidth/2);
                glScalef(1,1,-1);
                dbox(4,4,bridgeWidth/2,0,0,ironId,1,20,point(transDir*2*height*(csp-cs)+transDir*2,transDir*100*0.3+1,0));

            }

        }glPopMatrix();
    }
}

void background::archRod()
{
    double pi=M_PI;
    int i=0;
    for (double step=-pi; step<=pi; step+=.3,i++) {
        glPushMatrix();{
            glTranslatef(0,100*step,80*cos(step));
            dbox(4,4,80+60*cos(step)-80*cos(step)-1,0,0,ironId,1,20);

            if (i>=2 && i<=19) {
                int transDir=-1;
                if (step<0) transDir=1;
                dbox(4,4,80+60*cos(step)-80*cos(step)-1,0,0,ironId,1,20,point(0,transDir*100*0.3,0));
            }

        }glPopMatrix();
    }
}

void background::bridgeRod()
{
    double pi=M_PI;
    for (double step=-pi; step<=pi; step+=.1) {
        glPushMatrix();{
            glTranslatef(0,100*step,-15);
            double height=80*cos(step)+5;
            if (height>0) dbox(1,1,height,0,0,ironId,1,20);

        }glPopMatrix();
    }
}

void background::drawPlane()
{
    //plane
    //glColor3f(.2,.5,0);
    for (int i=0; i<waterSurfaces.size(); i++) waterSurfaces[i].draw();

    Plane4Pt(point(-1000,-1000,0),
             point(-1000,1000,0),
             point(-1000,1000,1000),
             point(-1000,-1000,1000),
             skyBackId).draw();

    Plane4Pt(point( 1000,-1000,0),
             point( 1000,1000,0),
             point( 1000,1000,1000),
             point(  1000,-1000,1000),
             skyFrontId).draw();

    Plane4Pt(point( 1000,-1000,0),
             point(-1000,-1000,0),
             point(-1000,-1000,1000),
             point( 1000,-1000,1000),
             skyLeftId).draw();

    Plane4Pt(point( 1000, 1000,0),
             point(-1000, 1000,0),
             point(-1000, 1000,1000),
             point( 1000, 1000,1000),
             skyRightId).draw();

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
        glTranslatef(bridgeWidth/4,0,120);
        archDown();
    }glPopMatrix();

    //arch down side2
    glPushMatrix();{
        glTranslatef(-bridgeWidth/4,0,120);
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

    glPushMatrix();{
        glTranslatef(bridgeWidth/4,0,200);
        archRodTopDown(30,2,19);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(bridgeWidth/4,0,120);
        archRodTopDown(40,7,14);
    }glPopMatrix();

    //road
    glPushMatrix();{
        glTranslatef(0,0,100);
        road();
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



void background::keyboardListener(unsigned char key){
    if (key=='h') highQlty=!highQlty;
}
void background::specialKeyListener(int key, int x,int y){}
void background::mouseListener(int button, int state, int x, int y){}



//void background::archDown()
//{
//    //glRotatef(90,0,1,0);
//    //glutSolidTorus(5,350,100,100);
//    double theta=0;
//    double circleTheta=0;
//    double pi=M_PI;

//    glPushMatrix();{
//        glTranslatef(0,0,120);
//        for (double step=-pi; step<=pi; step+=.05) {
//            glPushMatrix();{
//                glTranslatef(0,step*50,30*cos(step));
//                //glRotatef(-sin(step)*180/pi,1,0,0);
//                //glutSolidCube(10);
//                double x1=5;
//                double y1=step*50;
//                double z1=30*cos(step);

//                double x2=-5;
//                double y2=(step+.1)*50;
//                double z2=30*cos(step+.1);


//                Plane4Pt planeUpDown = Plane4Pt(point(x1,y1,z1),
//                                          point(x1,y2,z2),
//                                          point(x2,y2,z2),
//                                          point(x2,y1,z1));
//                Plane4Pt planeLeftWrite = Plane4Pt (point(x1,y1,z1),
//                                                    point(x1,y1,z1-10),
//                                                    point(x1,y2,z2-10),
//                                                    point(x1,y2,z2));
//                planeUpDown.draw();
//                planeLeftWrite.draw();

//                glTranslatef(0,0,-10);
//                planeUpDown.draw();

//                glTranslatef(-10,0,10);
//                planeLeftWrite.draw();

//            }glPopMatrix();
//        }
//    }glPopMatrix();


//    glPushMatrix();{
//        glTranslatef(0,0,20);
//        for (double step=-pi; step<=pi; step+=.05) {
//            glPushMatrix();{
//                glTranslatef(0,step*50,50*cos(step));
//                //glRotatef(-sin(step)*180/pi,1,0,0);
//                //glutSolidCube(10);
//                double x1=5;
//                double y1=step*50;
//                double z1=50*cos(step);

//                double x2=-5;
//                double y2=(step+.1)*50;
//                double z2=50*cos(step+.1);


//                Plane4Pt planeUpDown = Plane4Pt(point(x1,y1,z1),
//                                          point(x1,y2,z2),
//                                          point(x2,y2,z2),
//                                          point(x2,y1,z1));
//                Plane4Pt planeLeftWrite = Plane4Pt (point(x1,y1,z1),
//                                                    point(x1,y1,z1-10),
//                                                    point(x1,y2,z2-10),
//                                                    point(x1,y2,z2));
//                planeUpDown.draw();
//                planeLeftWrite.draw();

//                glTranslatef(0,0,-10);
//                planeUpDown.draw();

//                glTranslatef(-10,0,10);
//                planeLeftWrite.draw();

//            }glPopMatrix();
//        }
//    }glPopMatrix();
//    glScalef(1,125,5.5);


//    {
//        for (circleTheta=0; circleTheta<=2.0*pi; circleTheta+=0.05) {
//            //glVertex3f(10*cos(circleTheta),0,1/3.0*sin(circleTheta));
//            glPushMatrix();{
//                glTranslatef(5.0*cos(circleTheta),0,5*1/5.5*sin(circleTheta));
//                glBegin(GL_LINE_STRIP); {
//                    for (theta=-pi/1.2; theta<=pi/1.2; theta+=0.05) {
//                        glNormal3f(1,0,0);
//                        glVertex3f(0,theta,20*cos(theta));
//                    }
//                }
//                glEnd();
//            }glPopMatrix();
//        }
//    }

//}


//void background::archUp()
//{
//    double theta=0;
//    double circleTheta=0;
//    double pi=M_PI;


//    glScalef(1,100,3);

//    {
//        for (circleTheta=0; circleTheta<=2.0*pi; circleTheta+=0.05) {
//            //glVertex3f(10*cos(circleTheta),0,1/3.0*sin(circleTheta));
//            glPushMatrix();{
//                glTranslatef(5.0*cos(circleTheta),0,5*1/3.0*sin(circleTheta));
//                glBegin(GL_LINE_STRIP); {
//                    for (theta=-pi; theta<=pi; theta+=0.05) {
////                        double numc=M_2_PI/0.05;
////                        double numt=M_2_PI/0.05;
////                        double s=circleTheta;
////                        double t=theta;
////                        double x = cos(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
////                        double z = sin(t*M_2_PI/numt) * cos(s*M_2_PI/numc);
////                        double y = sin(s*M_2_PI/numc);
////                        glPushMatrix();{
////                            glScalef(1,1,1);
////                            glNormal3f(x,y,z);
////                        }glPopMatrix();
//                        glNormal3f(1,0,0);
//                        glVertex3f(0,theta,20*cos(theta));
//                    }
//                }
//                glEnd();
//            }glPopMatrix();
//        }
//    }

//}
