#include<GL/glut.h>
#include<GL/gl.h>
#include<stdio.h>

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    // glBegin(GL_LINES);
    // glVertex2f(200, 100);
    glutPostRedisplay();
    glutSwapBuffers();

}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Window name");
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}