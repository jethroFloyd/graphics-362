#include <vector>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <GL/glut.h>

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,std::vector<std::vector<int>>& ael) {
    float mx,x,temp;
    int i;
    if((y2-y1)<0) {
      temp=x1; x1=x2; x2=temp;
      temp=y1; y1=y2; y2=temp;
    }
    if((y2-y1)!=0) mx = (x2-x1)/(y2-y1);
    else mx = x2-x1;

    x=x1;
    for(i=y1; i<y2; i++) {                 
        ael[i].push_back(x);
        x+=mx;        
    }                 
}

void drawpixel(int x,int y){
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4) {
    std::vector<std::vector<int>> ael(500);
    int i,y;
    edgedetect(x1,y1,x2,y2, ael);    // call edge detect four times
    edgedetect(x2,y2,x3,y3, ael);    // once for each edge.
    edgedetect(x3,y3,x4,y4, ael);
    edgedetect(x4,y4,x1,y1, ael);
    for(int i = 0; i < 500 ; i++)
        std::sort(ael[i].begin(), ael[i].end());
    for(y=0;y<500;y++) {
        for(auto x_1 = ael[y].begin(), x_2 = x_1;x_1 != ael[y].end(); ){
            x_2 = x_1+1;
            if(x_2 == ael[y].end()) break;
            for(int x_cord = *x_1+1; x_cord < *x_2; x_cord++)
                drawpixel(x_cord,y);
            x_1 = x_2+1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x1=200,y1=300,x2=100,y2=100,x3=200,y3=500,x4=300,y4=100;
    glBegin(GL_LINE_LOOP);       // draw the boundary of the polygon
    glVertex2f(x1,y1);                   // to be filled.
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
    scanfill(x1,y1,x2,y2,x3,y3,x4,y4);       // call scanfill to fill the polygon
    glFlush();   // Usually students fail the lab because they forget glFlush.
}

void myinit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char **argv) { 
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);// 500 height is hardcoded
    glutInitWindowPosition(0,0);
    glutCreateWindow("scanfill");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}