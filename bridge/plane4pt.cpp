#include "plane4pt.h"

Plane4Pt::Plane4Pt(point pt1, point pt2, point pt3, point pt4) {
	pts.push_back(pt1); pts.push_back(pt2);
	pts.push_back(pt3); pts.push_back(pt4);
}

void Plane4Pt::draw() {
	glBegin(GL_QUADS); {
		FOR(i, pts.size()) {
                        point a = pts[i] - pts[(pts.size()+i-1)%sz(pts)];
                        point b = pts[(i+1)%sz(pts)] - pts[i];
			a = a.cross(b).unit();
			glNormal3d(V(a));
			glVertex3d(V(pts[0]));
		}
	} glEnd();
}
