#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>


GLenum doubleBuffer;
GLint thing1, thing2;


static void Init(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearAccum(0.0, 0.0, 0.0, 0.0);

    thing1 = glGenLists(1);
    glNewList(thing1, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    glRectf(-1.0, -1.0, 1.0, 0.0);
    glEndList();

    thing2 = glGenLists(1);
    glNewList(thing2, GL_COMPILE);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(0.0, -1.0, 1.0, 1.0);
    glEndList();
}

static void Reshape(int width, int height)
{

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void Key(unsigned char key, int x, int y)
{
    GLfloat m[] = {1, 0, 0, 0,  0.5, 1, 0, 0,     0, 0, 1, 0,     0, 0, 0, 1};
    GLfloat n[] = {1, 0, 0, 0,  -0.5, 1, 0, 0,    0, 0, 1, 0,     0, 0, 0, 1};
    glMatrixMode(GL_MODELVIEW);
    //glMultMatrixf(trans);
    glTranslatef(0.5, 0.5, 0);
    switch (key) {
        case '1':
            glScalef(0.33, 1, 1);
            break;
        case '2':
            glScalef(3, 1, 1);
            break;
        case '3':
            glRotatef(45, 1, 0, 0);
            break;
        case '4':
            glMultMatrixf(m);//shear transformation
            break;
        case '5':
            glMultMatrixf(n);//shear transformation
            break;
        case '6':
            glScalef(-1, 1, 1);
            break;
        case '7':
            glTranslatef(0, 0.2, 0);
            break;
        case '8':
            glTranslatef(0, -0.2, 0);
            break;
        case 27:
        exit(0);
    }
    glTranslatef(-0.5, -0.5, 0);
    //glMultMatrixf(revtrans);
    glutPostRedisplay();
}

static void Draw(void)
{

    float i=0;
	glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for(i=0;i<10*3.14;i+=0.0001){
        glVertex3f(cos(i)/2, sin(i)/2, 0.0);    
    }
    glEnd();
    glPopMatrix();

    if (doubleBuffer) {
	glutSwapBuffers();
    } else {
	glFlush();
    }
}

static void Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-sb") == 0) {
	    doubleBuffer = GL_FALSE;
	} else if (strcmp(argv[i], "-db") == 0) {
	    doubleBuffer = GL_TRUE;
	}
    }
}

int main(int argc, char **argv)
{
    printf("press 1 to scale about X-axis by 0.5\n");
    printf("press 2 to scale about X-axis by 2\n");
    printf("press 3 to rotate about X-axis by 45 degrees\n");
    printf("press 4 to apply sheer along X-axis of 2\n");
    printf("press 5 to apply sheer along X-axis of -2\n");
    printf("press 6 to reflect about X-axis\n");
    printf("press 7 to translate along Y-axis by 0.2\n");
    printf("press 8 to translate along Y-axis of -0.2\n");


    GLenum type;

    glutInit(&argc, argv);
    Args(argc, argv);

    type = GLUT_RGB | GLUT_ACCUM;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Accum Test");

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();
}
