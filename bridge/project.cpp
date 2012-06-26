#include "project.h"

project::project()
{
    //bg = background(point(0,0,0));

    pos = point(900,800,500);
    look = point(0,0,100);
    headDir = point(0,0,1);
    ang = angle(0,0,0);
    moveSpeed = 5;
    rotateSpeed=2;


    shapes.addShape(new background());
}

void project::init() {

    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1

    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.2f, 0.2f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

//    //Add directed light
//    GLfloat lightColor2[] = {0.5f, 0.0f, 0.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
//    //Coming from the direction (-1, 0.5, 0.5)
//    GLfloat lightPos2[] = {-1.0f, 0.5f, 0.5f, 0.0f};
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
//    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    cameraAngle = 0;	//// init the cameraAngle
    cameraAngleDelta = 0.03;
    rectAngle = 0;
    canDrawGrid = true;
    cameraHeight = 70;
    cameraRadius = 150;

    shapes.init();

}

void project::animate() {

}

void project::draw() {
    //gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(0, 100, 50,		0,0,0,		0,0,1);
    gluLookAt(P(pos),		P(look),		P(headDir));


    glPushMatrix();{
        //glTranslatef(pos.x,pos.y,pos.z);
        glBegin(GL_LINE);{
            glColor3f(0,1,0);
            glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
            glVertex3f(0,  150, 0);

            //X axis
            glColor3f(1,0,0);
            glVertex3f(-150, 0, 0);
            glVertex3f( 150, 0, 0);

            glColor3f(0,0,1);
            glVertex3f(0, 0, -150);
            glVertex3f(0, 0, 150);
        }glEnd();

    }
    glPopMatrix();

    shapes.draw();


}

void project::rotateXAxis(bool dir){
    if (dir) headDir=headDir.rotate(look-pos,-rotateSpeed);
    else headDir=headDir.rotate(look-pos,rotateSpeed);
}

void project::rotateYAxis(bool dir){
    point change;
    if (dir)    change = (look-pos).rotate(headDir,-rotateSpeed);
    else        change = (look-pos).rotate(headDir,rotateSpeed);
    look = change+pos;
}

void project::rotateZAxis(bool dir){
    int tempRotateSpeed = rotateSpeed;
    if (dir) tempRotateSpeed*=-1;

    point rotateAxis = (look-pos).cross(headDir);
    point change = (look-pos).rotate(rotateAxis,tempRotateSpeed);
    look = change+pos;
    headDir = headDir.rotate(rotateAxis,tempRotateSpeed);
}

void project::keyboardListener(unsigned char key, int x,int y) {

    shapes.keyboardListener(key,x,y);

    switch(key){

    case '1':	//reverse the rotation of camera
        cameraAngleDelta = -cameraAngleDelta;
        break;

    case '2':	//increase rotation of camera by 10%
        cameraAngleDelta *= 1.1;
        break;

    case '3':	//decrease rotation
        cameraAngleDelta /= 1.1;
        break;

    case '8':	//toggle grids
        canDrawGrid = 1 - canDrawGrid;
        break;

    case 'o' :
        rotateXAxis(0);
        break;

    case 'p' :
        rotateXAxis(1);
        break;
    case 'l' :
        rotateYAxis(0);
        break;

    case ';' :
        rotateYAxis(1);
        break;

    case '.' :
        rotateZAxis(0);
        break;
    case '/':
        rotateZAxis(1);
        break;

    case 27:	//ESCAPE KEY -- simply exit
        exit(0);
        break;

    default:
        break;
    }


}

void project::moveXAxis(bool dir){
    point change = (look-pos).cross(headDir).unit()*moveSpeed;
    if (dir) change = -change;
    pos = pos+change;
    look = look+change;
}

void project::moveYAxis(bool dir) {
    point change = (look-pos).unit()*moveSpeed;
    if (dir) change = -change;
    pos = pos+change;
    look = look + change;
}

void project::moveZAxis(bool dir) {
    point change = headDir.unit()*moveSpeed;
    if (dir) change = -change;
    pos = pos+change;
    look = look + change;
}

void project::specialKeyListener(int key, int x,int y) {
    //solarSystem.specialKeyListener(key,x,y);

    shapes.specialKeyListener(key,x,y);

    switch(key){
    case GLUT_KEY_DOWN:		//down arrow key
        moveYAxis(1);
        break;
    case GLUT_KEY_UP:		// up arrow key
        moveYAxis(0);
        break;

    case GLUT_KEY_RIGHT:
        moveXAxis(0);
        break;
    case GLUT_KEY_LEFT:
        moveXAxis(1);
        break;
    case GLUT_KEY_PAGE_UP:
        moveZAxis(0);
        break;
    case GLUT_KEY_PAGE_DOWN:
        moveZAxis(1);
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}

void project::mouseListener(int button, int state, int x, int y) {

    shapes.mouseListener(button,state,x,y);

    switch(button){
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
            cameraAngleDelta = -cameraAngleDelta;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}
