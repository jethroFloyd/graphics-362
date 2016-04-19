#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double R;

float round_value(float v)
{
  return floor(v + 0.5);
}
void LineDDA(void)
{
  int x=0,y=R, xc=0, yc=0;
  /* Find out whether to increment x or y */
  int p;
  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
  glBegin(GL_POINTS);
  /* Plot the first point */

  x=0;
	y=R;
	glVertex2d(x, y);
	p=1-R;
	for(x=0;x<=y;x++)
	{
		if (p<0){
			p=(p+(2*x)+1);
		}else{
			y=y-1;
			p=p+((2*(x-y)+1));
		}
		glVertex2d(xc+x,yc-y);
		glVertex2d(xc-x,yc-y);
		glVertex2d(xc+x,yc+y);
		glVertex2d(xc-x,yc+y);
		glVertex2d(xc+y,yc-x);
		glVertex2d(xc-y,yc-x);
		glVertex2d(xc+y,yc+x);
		glVertex2d(xc-y,yc+x);
	}
  glEnd();

  glFlush();
}
void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(-320 , 320 , -240 , 240);
}
int main(int argc, char **argv)
{
  printf("\nEnter Radius R:\n");
  scanf("%lf",&R);
  
  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("DDA_Line");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(LineDDA);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
  return 0;
}

