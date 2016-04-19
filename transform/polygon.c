#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


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
    GLfloat m[] = {1, 0, 0, 0,  3, 1, 0, 0,     0, 0, 1, 0,     0, 0, 0, 1};
    GLfloat n[] = {1, 0, 0, 0,  -3, 1, 0, 0,    0, 0, 1, 0,     0, 0, 0, 1};
    glMatrixMode(GL_MODELVIEW);
    switch (key) {
        case '1':
            glScalef(0.33, 1, 1);
            glutPostRedisplay();
            break;
        case '2':
            glScalef(3, 1, 1);
            glutPostRedisplay();
            break;
        case '3':
            glRotatef(45, 0, 0, 1);
            glutPostRedisplay();
            break;
        case '4':
            glMultMatrixf(m);
            glutPostRedisplay();
            break;
        case '5':
            glMultMatrixf(n);
            glutPostRedisplay();
            break;
        case '6':
            glScalef(-1, 1, 1);
            glutPostRedisplay();
            break;
        case '7':
            glTranslatef(0, 0.1, 0);
            glutPostRedisplay();
            break;
        case '8':
            glTranslatef(0, -0.1, 0);
            glutPostRedisplay();
            break;
        case 27:
        exit(0);
    }
}


static void Draw(void)
{

	glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glVertex3f(-0.7, -0.5, 0.0);
    glVertex3f(-0.7, -0.5, 0.0);
    glVertex3f(-0.2, -0.6, 0.0);
    glVertex3f(-0.2, -0.6, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
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
    printf("1 : to scale about X-axis to 1/3\n");
    printf("2 : to scale about X-axis by 3\n");
    printf("3 : to rotate about X-axis by 45 degrees\n");
    printf("4 : to apply sheer along X-axis of 3\n");
    printf("5 : to apply sheer along X-axis of -3\n");
    printf("6 : to reflect about X-axis\n");
    printf("7 : to translate along Y-axis by 0.1\n");
    printf("8 : to translate along Y-axis of -0.1\n");
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
