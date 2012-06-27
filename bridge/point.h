/*
 * point.h
 *
 *  Created on: Jun 1, 2012
 *      Author: enzam
 */

#ifndef point_H_
#define point_H_

#include <iostream>
#include <math.h>
#include "etemplate.h"
using namespace std;

#define P(pt) pt.x,pt.y,pt.z

class point{
public:
	double x,y,z;
        explicit point(double _x=0,double _y=0,double _z=0) {x=_x;y=_y;z=_z;}
        static point UnitX, UnitY, UnitZ, Zero;

    friend point operator+(const point &a, const point &b) {	return point(a.x+b.x, a.y+b.y, a.z+b.z);}
    friend point operator-(const point &a)          {    return point (-a.x, -a.y, -a.z);}
    friend point operator-(const point &a,const point &b) {	return point(a.x-b.x, a.y-b.y, a.z-b.z);}
    friend point operator*(double a,point b) {	return point(a*b.x, a*b.y, a*b.z);}
    friend point operator*(point b,double a) {	return a*b;}
    friend point operator/(point b,double a) {	return point(b.x/a, b.y/a, b.z/a);}

        double sqrMag() { return sqr(x)+sqr(y)+sqr(z); } // square of magnitude
	double mag(){ return sqrt(sqrMag()); } //magnitude
	void normalize(){ double d = mag(); x/=d; y/=d; z/=d; }
        point unit() { point ret = *this;	ret.normalize(); return ret; }

        static double dot(point a, point b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
        static point cross(point a, point b){ return point( a.y*b.z - a.z*b.y , a.z*b.x - a.x*b.z , a.x*b.y - a.y*b.x ); }

        double dot(point b) { return dot(*this, b); }
        point cross(point b) { return cross(*this, b); }
    static double angle(point a, point b) { return acos(dot(a,b)/(a.mag()*b.mag())); }
        double angleWith(point b) { return angle(*this, b); }

        friend point operator*(point a, point b) { return cross(a, b); }
        friend double operator^(point a, point b) { return dot(a, b); }

        double projectionLength(point on) { on.normalize(); return dot(on);}
        point projectionPoint(point on) { on.normalize(); return on * projectionLength(on);}

        point rotate(point axis, double angle) {
                double pi = 2.0*acos(0.0);
                angle = pi/180.0*angle;
                axis.normalize();
                point normal = (axis * *this).unit();
                point mid = (normal * axis).unit();
                double r = projectionLength(mid);
                return (r*mid*cos(angle) + r*normal*sin(angle) + projectionPoint(axis));
        }
    friend ostream& operator<<(ostream& out, point a) { return out<<"["<<a.x<<","<<a.y<<","<<a.z<<"]";}

};

#endif /* point_H_ */
