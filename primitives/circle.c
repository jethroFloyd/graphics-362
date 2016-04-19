#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <math.h>
#include <stdio.h>
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
      glColor3f (0.0, 0.0, 0.0);

      glVertex3f (0.1, 0.1, 0.0);
      glVertex3f (0.9, 0.1, 0.0);
      glVertex3f (0.9, 0.9, 0.0);
      glVertex3f (0.1, 0.9, 0.0);

    glEnd();

    glFlush();
    // DrawCircle(0.5, 0.5, 0.2, 5);
}

void DrawCircle()
{
    float cx = 0.5, cy = 0.5, r = 0.2, num_segments = 50;
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
    glFlush();
}


void Initialize() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {
    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(950, 950);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Universum");
    Initialize();
    Draw();
    glutDisplayFunc(DrawCircle);
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(1.0, 1.0, 1.0);
    // DrawCircle(0.5, 0.5, 0.2, 5);

    glutMainLoop();
    return 0;

}