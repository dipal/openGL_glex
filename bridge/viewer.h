/*
 * Movement.h
 *
 *  Created on: Jun 2, 2012
 *      Author: enzam
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "vector.h"
#include "shapeinterface.h"

class Viewer: public ShapeInterface {
	enum ViewerOps {
		UP_DOWN = 1, LEFT_RIGHT, FOR_BACKWARD, ROLL, PITCH, YAW
	};
	Vector eyePos, lookAt;
	Vector headDir;

	double upDownRatio;
	double leftRightRatio;
	double forBackwardRatio;
	double yawChange;
	double pitchChange;
	double rollChange;

	double rotX, rotY, rotZ;
	queue<pair<int, int> > queuedOps;
	pair<ViewerOps, int> key2func[256];

	bool buttonDown[20];
	int mousex, mousey;
        bool animeActive;

public:
	Viewer(Vector eye, Vector look, Vector head) :
			eyePos(eye), lookAt(look), headDir(head)
			{
					memset(buttonDown, 0, sizeof(buttonDown));
	}

	void initKeyListener() {
		key2func['w'] = mp(UP_DOWN, 0);
		key2func['s'] = mp(UP_DOWN, 1);

		key2func['a'] = mp(YAW, 0);
		key2func['d'] = mp(YAW, 1);

		key2func['q'] = mp(PITCH, 0);
		key2func['z'] = mp(PITCH, 1);

		key2func['8'] = mp(FOR_BACKWARD, 0);
		key2func['5'] = mp(FOR_BACKWARD, 1);

		key2func['4'] = mp(LEFT_RIGHT, 0);
		key2func['6'] = mp(LEFT_RIGHT, 1);

		key2func['7'] = mp(ROLL, 0);
		key2func['9'] = mp(ROLL, 1);

	}

	void init() {
//		upDownRatio = 5;
//		leftRightRatio = 5;
//		forBackwardRatio = 5;

		upDownRatio = leftRightRatio = forBackwardRatio = 10;

                yawChange = 0.1;
		pitchChange = 0.1;
		rollChange = 0.1;

		initKeyListener();
	}

	void moveLeftRight(int type) { //0 - left, 1 - right
		Vector change = (lookAt - eyePos).cross(headDir).unit()
				* leftRightRatio;

		if (!type) {
			change = change * -1;
		} //if right

		lookAt = lookAt + change;
		eyePos = eyePos + change;
	}

	void moveUpDown(int type) {
		Vector change = headDir.unit() * upDownRatio;

		if (type) {
			change = change * -1;
		} //if up

		lookAt = lookAt + change;
		eyePos = eyePos + change;
	}

	void moveForBackward(int type) {
		Vector change = (lookAt - eyePos).unit() * forBackwardRatio;

		if (type) {
			change = change * -1;
		} //if forward

		lookAt = lookAt + change;
		eyePos = eyePos + change;
	}

	void rotateYaw(int type, double multi = 1.0) {
		double rotAngle = yawChange * multi;
		if (type)
			rotAngle = rotAngle * -1;
		lookAt = (lookAt - eyePos).rotate(headDir, rotAngle) + eyePos;

		rotZ += rotAngle;
	}

	void rotatePitch(int type, double multi = 1.0) {
		double rotAngle = pitchChange * multi;
		if (type)
			rotAngle = rotAngle * -1;
		Vector rotAxis = (lookAt - eyePos) * headDir;
		lookAt = (lookAt - eyePos).rotate(rotAxis, rotAngle) + eyePos;
		headDir = headDir.rotate(rotAxis, rotAngle);

		rotY -= rotAngle;
	}

	void rotateRoll(int type, double multi = 1.0) {
		double rotAngle = rollChange * multi;
		if (type)
			rotAngle = rotAngle * -1;
		headDir = headDir.rotate(lookAt - eyePos, rotAngle);

		rotX += rotAngle;
	}

	void execOperation(int opType, int type) {
		switch (opType) {
		case UP_DOWN: {
			moveUpDown(type);
			break;
		}
		case LEFT_RIGHT: {
			moveLeftRight(type);
			break;
		}
		case FOR_BACKWARD: {
			moveForBackward(type);
			break;
		}
		case ROLL: {
			rotateRoll(type);
			break;
		}
		case PITCH: {
			rotatePitch(type);
			break;
		}
		case YAW: {
			rotateYaw(type);
			break;
		}
		}
	}


        void animate()
        {
            if (!animeActive) return ;

            if(eyePos.x==150 && eyePos.y==-300 && eyePos.z>=50 && eyePos.z<200) {
                moveUpDown(0);
                return ;
//                double rotAngle=90;
//                lookAt = (lookAt - eyePos).rotate(headDir, rotAngle) + eyePos;
//                rotZ += rotAngle;
            }

            if (eyePos.x==150 && eyePos.y<=-300 && eyePos.y>-400 && eyePos.z==200) {
                moveLeftRight(0);
                return ;
            }

            if (eyePos.x<=150 && eyePos.x>0 && eyePos.y==-400 && eyePos.z==200) {
                moveForBackward(0);
                return ;
            }

            if (eyePos.x==0 && eyePos.y==-400 && eyePos.z==200) {
                double rotAngle=(M_PI/180.0)*(-90);
                lookAt = (lookAt - eyePos).rotate(headDir, rotAngle) + eyePos;
                rotZ += rotAngle;
                moveForBackward(0);
                return ;
            }

            if (eyePos.x<10 && eyePos.y>=-400 && eyePos.y<400) {
                moveForBackward(0);

                if (eyePos.z>120) moveUpDown(1);
                return ;
            }

            if (eyePos.x<10 && eyePos.y==400) {
                double rotAngle=(M_PI/180.0)*(90);
                lookAt = (lookAt - eyePos).rotate(headDir, rotAngle) + eyePos;
                rotZ += rotAngle;
                moveForBackward(1);
                moveForBackward(1);
                return ;
            }

            if (eyePos.x>10 && eyePos.x<800 && eyePos.y==400) {
                moveForBackward(1);
                return ;
            }

            if (eyePos.x>=800 && eyePos.y<=400 && eyePos.y>-300) {
                moveLeftRight(0);
                return ;
            }
            if (eyePos.y==-300 && eyePos.x!=0) {
                moveForBackward(0);
                return ;
            }

            /*if (eyePos.x==0 && eyePos.y>=-400) {
                moveForBackward(0);
                return ;
            }*/
            //moveForBackward(0);
        }

	virtual void keyboardListener(unsigned char key) {
		execOperation(key2func[key].first, key2func[key].second);
                if (key=='m') animeActive=true;
                if (key=='n') animeActive=false;
                if (key=='r') {
                    eyePos=Vector(800,-300,50);
                    lookAt=Vector(0,-300,50);
                    headDir=Vector(0,0,1);
                }
	}

	void draw() {
		gluLookAt(
	            V(eyePos),
	            V(lookAt),
	            V(headDir)
			);
	}

	void mouseListener(int button, int state, int x, int y)
	{
		buttonDown[button] = (state == GLUT_DOWN) ? true : false;
		mousex = x, mousey = y;
		motionListener(x, y);
	}

	virtual void motionListener(int x, int y) {
		double dx = abs(x - mousex) / 5.; int xtype = (x > mousex);
		double dy = abs(y - mousey) / 5.; int ytype = (y > mousey);
		mousex = x, mousey = y;

		if(buttonDown[GLUT_LEFT_BUTTON]) {
			rotateYaw(-xtype, dx);

			rotatePitch(ytype, dy);
		}

		if(buttonDown[3]) {
			moveForBackward(0);
		}
		if(buttonDown[4]) {
			moveForBackward(1);
		}

		glutPostRedisplay();
	}
};

#endif /* MOVEMENT_H_ */
