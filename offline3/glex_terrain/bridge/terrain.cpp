#include "terrain.h"
Terrain::Terrain(string filename, double height,point inpos,point incolor)
{
    Image* image = loadBMP(filename.c_str());
    init(image->width, image->height);
    for(int y = 0; y < image->height; y++) {
        for(int x = 0; x < image->width; x++) {
            unsigned char grayvalue =
                    (unsigned char)image->pixels[3 * (y * image->width + x)];
            double h = height * ((grayvalue / 255.0) - 0.5);
            setHeight(x, y, h);
        }
    }

    color=incolor;
    pos=inpos;
    delete image;
    computeNormals();
}

void Terrain::setHeight(int x, int z, double y) {
        data[z][x] = y;
        computedNormals = false;
}

void Terrain::init(int w2, int h2)
{
    data.clear();
    for (int i=0; i<w2; i++)
    {
        vector<double> tdouble;
        vector<point> tpoint;
        data.push_back(tdouble);
        normals.push_back(tpoint);
        for (int j=0; j<h2; j++)
        {
            double d;
            point p;
            data[i].push_back(d);
            normals[i].push_back(p);
        }
    }
    computedNormals = false;
}


double Terrain::getHeight(int x, int z) {
        return data[z][x];
}

//Computes the normals, if they haven't been computed yet
void Terrain::computeNormals() {
        if (computedNormals) {
                return;
        }

        //Compute the rough version of the normals
        int h=data.size();
        int w=data[0].size();
        vector<vector<point> > normals2;

        for (int i=0; i<h; i++)
        {
            vector<point> tvector;
            normals2.push_back(tvector);
            for (int j=0; j<w; j++)
            {
                point p;
                normals2[i].push_back(p);
            }
        }

        for(int z = 0; z < h; z++) {
            for(int x = 0; x < w; x++) {
                point sum(0.0, 0.0, 0.0);

                point out;
                if (z > 0) {
                        out = point(0.0, data[z - 1][x] - data[z][x], -1.0);
                }
                point in;
                if (z < h - 1) {
                        in = point(0.0, data[z + 1][x] - data[z][x], 1.0);
                }
                point left;
                if (x > 0) {
                        left = point(-1.0, data[z][x - 1] - data[z][x], 0.0);
                }
                point right;
                if (x < w - 1) {
                        right = point(1.0, data[z][x + 1] - data[z][x], 0.0);
                }

                if (x > 0 && z > 0) {
                    point tp = out.cross(left);
                    tp.normalize();
                    sum = sum+tp;
                }
                if (x > 0 && z < h - 1) {
                    point tp = left.cross(in);
                    tp.normalize();
                    sum = sum + tp;
                }
                if (x < w - 1 && z < h - 1) {
                    point tp = in.cross(right);
                    tp.normalize();
                    sum = sum+tp;
                }
                if (x < w - 1 && z > 0) {
                    point tp  = right.cross(out);
                    tp.normalize();
                    sum = sum+tp;
                }

                normals2[z][x] = sum;
        }
    }

    const double FALLOUT_RATIO = 0.5;
    for(int z = 0; z < h; z++) {
        for(int x = 0; x < w; x++) {
            point sum = normals2[z][x];

            if (x > 0) {
                    sum = sum + normals2[z][x - 1] * FALLOUT_RATIO;
            }
            if (x < w - 1) {
                    sum = sum + normals2[z][x + 1] * FALLOUT_RATIO;
            }
            if (z > 0) {
                    sum = sum + normals2[z - 1][x] * FALLOUT_RATIO;
            }
            if (z < h - 1) {
                    sum = sum + normals2[z + 1][x] * FALLOUT_RATIO;
            }
            if (sum.mag() == 0) {
                    sum = point(0.0, 1.0, 0.0);
            }

            normals[z][x] = sum;
        }
    }

    computedNormals = true;
}

//Returns the normal at (x, z)
point Terrain::getNormal(int x, int z) {
        if (!computedNormals) {
                computeNormals();
        }
        return normals[z][x];
}
