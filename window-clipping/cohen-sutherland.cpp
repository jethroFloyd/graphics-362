#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <GL/glut.h>

typedef int OutCode;
bool drawClipped = false;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000


int xmin = 150, ymin = 150, xmax = 400, ymax = 400;

OutCode ComputeOutCode(double x, double y) {
	OutCode code;
	code = INSIDE;          // initialised as being inside of clip window
	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
bool CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if(accept){
		glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
		glEnd();
	}
	return accept;
}

void displayWithClip(){

	// Drawing the boundary.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
    glPointSize(2.0);
    GLfloat a1 = 400, b1 = 150, a2 = 150, b2 = 150, a3 = 150, b3 = 400, a4 = 400, b4 = 400;
    glBegin(GL_LINE_LOOP);       // draw the boundary of the polygon
    glVertex2f(a1,b1);                   // to be filled.
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glVertex2f(a4,b4);
    glEnd();
    glFlush();
    printf("hello\n");
    // Draw the clipped polygon
    glColor3f(1.0,0.0,0.0);
    double x1=200,y1=300,x2=100,y2=100,x3=200,y3=500,x4=300,y4=100;
    CohenSutherlandLineClipAndDraw(x1,y1,x2,y2);
	CohenSutherlandLineClipAndDraw(x2,y2,x3,y3);
    CohenSutherlandLineClipAndDraw(x3,y3,x4,y4);
    CohenSutherlandLineClipAndDraw(x4,y4,x1,y1);
    glFlush();
}


void display() {
	if(drawClipped) return displayWithClip();
    glClear(GL_COLOR_BUFFER_BIT);
    printf("Display is called\n");
    glColor3f(0.0,0.0,1.0);
    double x1=200,y1=300,x2=100,y2=100,x3=200,y3=500,x4=300,y4=100;
    glBegin(GL_LINE_LOOP);       // draw the boundary of the polygon
    glVertex2f(x1,y1);                   // to be filled.
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
    //glFlush();   // Usually students fail the lab because they forget glFlush.
    glColor3f(0.0,1.0,0.0);
    glPointSize(2.0);
    GLfloat a1 = 400, b1 = 150, a2 = 150, b2 = 150, a3 = 150, b3 = 400, a4 = 400, b4 = 400;
    glBegin(GL_LINE_LOOP);       // draw the boundary of the polygon
    glVertex2f(a1,b1);                   // to be filled.
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glVertex2f(a4,b4);
    glEnd();
    glFlush();
}


void myinit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
static void Key(unsigned char key, int x, int y){
	
    switch (key) {
      case '1':
      	printf("pressed 1\n");
      	drawClipped = false;
      	glutPostRedisplay();
		break;
      case '2':
      	printf("pressed 2\n");
		drawClipped = true;
		glutPostRedisplay();
		break;
	default:
		printf("Unknown\n");
    }
}

int main(int argc,char **argv) { 
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);// 500 height is hardcoded
    glutInitWindowPosition(0,0);
    glutCreateWindow("scanfill");
    glutKeyboardFunc(Key);
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();

    return 0;
}