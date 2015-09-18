#include "mountainview.h"
#include <math.h>
#include <iostream>
using namespace std;
MountainView::MountainView()
{
}


void MountainView::init()
{
    resourcePath = "../resource";
    mountain = new Terrain(resourcePath+"/testHM.bmp",150);
    //water = new Terrain(resourcePath+"/waterhm.bmp",10,point(100,-200,-65));
    for (int i=0; i<12; i++)
    {
        vector<Terrain*> tvector;
        water.push_back(tvector);
        for (int j=0; j<12; j++)
        {
            Terrain *twater = new Terrain(resourcePath+"/waterhm.bmp",10,point(-60+i*60,-540+j*60,-60));
            water[i].push_back(twater);
        }
    }
    waterUpDir=.1;
}

void MountainView::keyboardListener(unsigned char key)
{
    //if (key=='j') waterUpDir=-waterUpDir;
}

void MountainView::drawTerrain(Terrain *terrain,point color)
{
    glPushMatrix();{
        glTranslatef(terrain->pos.x,terrain->pos.y,terrain->pos.z);
        glColor3f(color.x,color.y,color.z);
        glRotatef(90,1,0,0);
        for(int z = 0; z < terrain->data.size() - 1; z++) {
            //Makes OpenGL draw a triangle at every three consecutive vertices
            glBegin(GL_TRIANGLE_STRIP);
            for(int x = 0; x < terrain->data[0].size(); x++) {
                point normal = terrain->getNormal(x, z);
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(x, terrain->getHeight(x, z), z);
                normal = terrain->getNormal(x, z + 1);
                glNormal3f(normal.x, normal.y, normal.z);
                glVertex3f(x, terrain->getHeight(x, z + 1), z + 1);
            }
            glEnd();
        }
    }glPopMatrix();

}

void MountainView::animate()
{
    //waterUpDir=0;
    if (fabs(water[0][0]->pos.z-(-65.0))<=1e-5 || fabs(water[0][0]->pos.z-(-30.0))<=1e-5) waterUpDir=-waterUpDir;

    //cout<<water[0][0]->pos.z<<" "<<waterUpDir<<endl;
    point waterSpeed = point(1,0,waterUpDir);
    for (int i=0; i<water.size(); i++)
    {
        for (int j=0; j<water[i].size(); j++)
        {
            water[i][j]->pos = water[i][j]->pos + waterSpeed;
            if (water[i][j]->pos.x>=660) water[i][j]->pos.x=-60;
        }
    }
}

void MountainView::draw()
{
    drawTerrain(mountain);
    for (int i=0; i<water.size(); i++)
    {
        for (int j=0; j<water[i].size(); j++)
        {
            drawTerrain(water[i][j],point(.0,.5,.6));
        }
    }
    //drawTerrain(water,point(.0,.5,.6));
}
