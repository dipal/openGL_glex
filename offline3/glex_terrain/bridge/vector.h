/*
 * vector.h
 *
 *  Created on: Jun 1, 2012
 *      Author: enzam
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "etemplate.h"

class Vector{
public:
	double x,y,z;
	explicit Vector(double _x=0,double _y=0,double _z=0) {x=_x;y=_y;z=_z;}
//	static Vector UnitX, UnitY, UnitZ, Zero;

    friend Vector operator+(const Vector &a, const Vector &b) {	return Vector(a.x+b.x, a.y+b.y, a.z+b.z);}
    friend Vector operator-(const Vector &a)          {    return Vector (-a.x, -a.y, -a.z);}
    friend Vector operator-(const Vector &a,const Vector &b) {	return Vector(a.x-b.x, a.y-b.y, a.z-b.z);}
    friend Vector operator*(double a,Vector b) {	return Vector(a*b.x, a*b.y, a*b.z);}
    friend Vector operator*(Vector b,double a) {	return a*b;}
    friend Vector operator/(Vector b,double a) {	return Vector(b.x/a, b.y/a, b.z/a);}
    friend bool operator==(Vector a, Vector b) {    return EQ(a.x, b.x) && EQ(a.y, b.y) && EQ(a.z, b.z); }

	double sqrMag() { return sqr(x)+sqr(y)+sqr(z); } // square of magnitude
	double mag() { return sqrt(sqrMag()); } //magnitude
	void normalize(){ double d = mag(); x/=d; y/=d; z/=d; }
	Vector unit() { Vector ret = *this;	ret.normalize(); return ret; }

	static double dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
	static Vector cross(Vector a, Vector b){ return Vector( a.y*b.z - a.z*b.y , a.z*b.x - a.x*b.z , a.x*b.y - a.y*b.x ); }

	double dot(Vector b) { return dot(*this, b); }
	Vector cross(Vector b) { return cross(*this, b); }
    static double angle(Vector a, Vector b) {
    	double sangle = asin ( cross(a, b).mag() / (a.mag() * b.mag()) );
    	double cangle = acos(dot(a,b)/(a.mag()*b.mag()));
    	if(cangle <= M_PI / 2) return sangle;
    	if(sangle > 0) return cangle;
    	else return -cangle;
    }
	double angleWith(Vector b) { return angle(*this, b); }

	friend Vector operator*(Vector a, Vector b) { return cross(a, b); }
	friend double operator^(Vector a, Vector b) { return dot(a, b); }


	double projectionLength(Vector on) { on.normalize(); return dot(on);}
	Vector projectionVector(Vector on) { on.normalize(); return on * projectionLength(on);}

	Vector rotate(Vector axis, double angle) {
		axis.normalize();
		if((axis * *this).mag() < EPS) return *this;
		Vector normal = (axis * *this).unit();
		if((normal * axis).mag() < EPS) return *this;
		Vector mid = (normal * axis).unit();
		double r = projectionLength(mid);
		return (r*mid*cos(angle) + r*normal*sin(angle) + projectionVector(axis));
	}

	friend ostream& operator<<(ostream& out, Vector a) { return out<<"["<<a.x<<","<<a.y<<","<<a.z<<"]";}
};

#endif /* VECTOR_H_ */
