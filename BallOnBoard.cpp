#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include<windows.h>
// Checkerboard properties
float boardSize = 15.0f;

// Sphere properties
float sphereRadius = 2.0f;
float sphereX = 0.0f;
float sphereY = sphereRadius;
float sphereZ = 0.0f;
float sphereSpeed = 0.1f;
int sphereDirection = 1;  //speed of bouncing

// Lighting properties
float spotlightPosition[] = { 0.0f, 10.0f, 0.0f, 1.0f };
float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };
float spotlightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

void drawCheckerboard()
{
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    for (float x = -boardSize / 2.0f; x < boardSize / 2.0f; x += 1.0f)
    {
        for (float z = -boardSize / 2.0f; z < boardSize / 2.0f; z += 1.0f)
        {
            glVertex3f(x, 0.0f, z);  //X Y Z VALUES
            glVertex3f(x + 1.0f, 0.0f, z);
            glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
            glVertex3f(x, 0.0f, z + 1.0f);
        }
        //glColor3f(1.0,1.0,1.0);
    }
    glEnd();
}

void drawSphere()
{
    glPushMatrix();
    glTranslatef(sphereX, sphereY, sphereZ);
    glColor3f(0.5f, 1.0f, 1.0f);
    glutSolidSphere(sphereRadius, 50, 50);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f, 10.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT1, GL_POSITION, spotlightPosition);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);

    drawCheckerboard();
    drawSphere();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        sphereX -= sphereSpeed;
        break;
    case 'd':
        sphereX += sphereSpeed;
        break;
    case 'w':
        sphereZ -= sphereSpeed;
        break;
    case 's':
        sphereZ += sphereSpeed;
        break;
    }

    // Check if the sphere is out of bounds
    if (sphereX < -boardSize / 2.0f + sphereRadius || sphereX > boardSize / 2.0f - sphereRadius ||
        sphereZ < -boardSize / 2.0f + sphereRadius || sphereZ > boardSize / 2.0f - sphereRadius)
    {
        // Bounce back
        sphereDirection = -sphereDirection;
    }

    // Keep the sphere on the checkerboard
    sphereX = fmaxf(-boardSize / 2.0f + sphereRadius, fminf(boardSize / 2.0f - sphereRadius, sphereX));
    sphereZ = fmaxf(-boardSize / 2.0f + sphereRadius, fminf(boardSize / 2.0f - sphereRadius, sphereZ));

    glutPostRedisplay();
}

void update(int value)
{
    // Roll the sphere
    sphereY -= sphereSpeed * sphereDirection;

    // Reverse the direction when the sphere hits the top or bottom of the checkerboard
    if (sphereY < sphereRadius || sphereY > boardSize / 2.0f - sphereRadius)
    {
        sphereDirection = -sphereDirection;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutCreateWindow("Solid Sphere on Checkerboard");
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spotlightColor);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}