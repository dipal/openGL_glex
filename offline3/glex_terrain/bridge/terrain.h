#ifndef TERRAIN_H
#define TERRAIN_H


#include <point.h>
#include <vector>
#include <string>
#include <imageloader.h>
#include <iostream>

using namespace std;

class Terrain
{

public:
    Terrain(string filename, double height,point inpos=point(0,0,0),point incolor=point(0,1,0));
    Terrain(){};

    void init(int,int);
    void setHeight(int x, int z, double y);
    double getHeight(int x, int z);
    void computeNormals();
    point getNormal(int x, int z) ;

    point pos;
    point color;
    vector<vector<double> > data;
    vector<vector<point> > normals;
    bool computedNormals; //Whether normals is up-to-date

};

#endif // TERRAIN_H
