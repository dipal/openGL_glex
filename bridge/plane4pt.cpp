#include "plane4pt.h"

Plane4Pt::Plane4Pt(Vector pt1, Vector pt2, Vector pt3, Vector pt4) {
	pts.push_back(pt1); pts.push_back(pt2);
	pts.push_back(pt3); pts.push_back(pt4);
}

void Plane4Pt::draw() {
	glBegin(GL_QUADS); {
		FOR(i, pts.size()) {
			Vector a = pts[i] - pts[(pts.size()+i-1)%sz(pts)];
			Vector b = pts[i+1] - pts[i];
			a = a.cross(b).unit();
			glNormal3d(V(a));
			glVertex3d(V(pts[0]));
		}
	} glEnd();
}
