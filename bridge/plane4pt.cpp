#include "plane4pt.h"

Plane4Pt::Plane4Pt(point pt1, point pt2, point pt3, point pt4) {
	pts.push_back(pt1); pts.push_back(pt2);
	pts.push_back(pt3); pts.push_back(pt4);
}

void Plane4Pt::draw(GLuint textureId,double xRepeat,double yRepeat) {
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        double texture[][2]={{0,0},{1,0},{1,1},{0,1}};
	glBegin(GL_QUADS); {
		FOR(i, sz(pts)) {
                        point a = pts[i] - pts[(pts.size()+i-1)%sz(pts)];
                        point b = pts[(i+1)%sz(pts)] - pts[i];
			a = a.cross(b).unit();
			glNormal3d(V(a));
                        glTexCoord2d(texture[i][0]*xRepeat,texture[i][1]*yRepeat);
			glVertex3d(V(pts[i]));
		}
	} glEnd();

        glDisable(GL_TEXTURE_2D);
}
