#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include<windows.h>

int rFlag = 0;
GLfloat PEACH[] = { 1.0, 1.0, 0.711 , 0.5 };
GLfloat WHITE[] = { 1, 1, 1 };
GLfloat BLACK[] = { 0, 0, 0 };
int flag = 4;

// Torus properties
float torusRadius = 2.0f;
float torusY = torusRadius;
float torusSpeed = 0.1f;
float torusDirection = 1.0f;

float cubeSize = 2.0f;
float cubeX = 2.0f;
// float cubeY = cubeSize / 2.0f;
float cubeY = 6.0f;
float cubeZ = 4.0f;
float cubeSpeed = 0.1f;
float angle = 10;

// Checkerboard properties
float boardSize = 15.0f;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
// Sphere properties
float sphereRadius = 2.0f;
float sphereX = 0.0f;
float sphereY = sphereRadius;
float sphereZ = 0.0f;
float sphereSpeed = 0.1f;
float moveSpeed = 0.1f;
int sphereDirection = 1.0;  //speed of bouncing
float r, g, b;

// Lighting properties
float spotlightPosition[] = { 0.0f, 10.0f, 0.0f, 1.0f };
float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };
float spotlightColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

void drawCheckerboard()
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    for (float x = -boardSize / 2.0f; x < boardSize / 2.0f; x += 1.0f)
    {
        for (float z = -boardSize / 2.0f; z < boardSize / 2.0f; z += 1.0f)
        {
            glVertex3f(x, 0.0f, z);  //X Y Z VALUES
            glVertex3f(x + 1.0f, 0.0f, z);
            glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
            glVertex3f(x, 0.0f, z + 1.0f);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                (int)(x + z) % 2 == 0 ? BLACK : PEACH);
        }
    }
    
    glEnd();
}

void drawSphere()
{
    glPushMatrix();
    glTranslatef(sphereX, sphereY, sphereZ);
    glColor3f(1.0, 0.0, 0.0);
    // void glutSolidSphere(GLdouble radius,
    //                  GLint slices, GLint stacks);
    glutSolidSphere(sphereRadius, 50, 50);
    
    glPopMatrix();
}

void drawWireSphere()
{
    glPushMatrix();
    glTranslatef(sphereX, sphereY, sphereZ);
    glColor3f(1.0, 0.0, 0.0);
    // void glutSolidSphere(GLdouble radius,
    //                  GLint slices, GLint stacks);
    glutWireSphere(sphereRadius, 50, 50);
    glPopMatrix();
}

void drawTorus()
{
    glPushMatrix();
    glTranslatef(0.0f, torusY, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.6f, torusRadius, 20, 25);
    glPopMatrix();
}

void drawWireTorus()
{
    glPushMatrix();
    glTranslatef(0.0f, torusY, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireTorus(0.6f, torusRadius, 20, 25);
    glPopMatrix();
}

void drawCube()
{
    glPushMatrix();
    glTranslatef(cubeX, cubeY, cubeZ);
    glColor3f(1.0f, 0.750f, 0.0f);
    glutSolidCube(cubeSize);
    glPopMatrix();
}

void drawCone(GLdouble r, GLdouble h, int n) {

    GLdouble fi;
    double dphi = 2 * M_PI / n;

    glBegin(GL_LINE_LOOP);
    for (fi = 0; fi < 2 * M_PI; fi += dphi) {
        glVertex3f(0, 0, h);
        glVertex3f(r * cos(fi), r * sin(fi), 0);
        glVertex3f(r * cos(fi + dphi), r * sin(fi + dphi), 0);
    }
    glEnd();
}

// void rotate_around_line(GLdouble x0, GLdouble y0, GLdouble z0, GLdouble u1, GLdouble u2, GLdouble u3, GLdouble kut)
// {
//     double vek[3] = { u1 - x0, u2 - y0, u3 - z0 };


//     glTranslatef(x0, y0, z0);
//     glRotatef(-kut, vek[0], vek[1], vek[2]);
//     glTranslatef(-x0, -y0, -z0);
// }


void display()
{
    GLfloat mat_ambient[] = { 0.0f,0.0f,0.0f,0.0f };
    GLfloat mat_diffuse[] = { 0.3f,0.3f,0.0f,0.0f };
    GLfloat mat_specular[] = { 0.0f,0.0f,0.0f,0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f, 10.0f, 20.0f, lookAtX, lookAtY, lookAtZ, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT1, GL_POSITION, spotlightPosition);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);
    glPushMatrix();


    glColor3f(1.0, 1.0, 0.0);
    drawCheckerboard();

    glPopMatrix();

    if (flag == 0)
        drawSphere();
    else if (flag == 1)
        drawTorus();
    else if (flag == 2)
        drawCube();
    else if (flag == 3)
        drawWireSphere();
    else if (flag == 4)
        drawWireTorus();

    glutSwapBuffers();
}


void specialKeyboardCallback(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        lookAtY -= moveSpeed;

        break;
    case GLUT_KEY_DOWN:
        lookAtY += moveSpeed;
        break;
    case GLUT_KEY_LEFT:
        lookAtX += moveSpeed;
        break;
    case GLUT_KEY_RIGHT: lookAtX -= moveSpeed;
        break;
    }
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
    if (sphereX<-boardSize / 2.0f + sphereRadius || sphereX>boardSize / 2.0f - sphereRadius ||
        sphereZ<-boardSize / 2.0f + sphereRadius || sphereZ>boardSize / 2.0f - sphereRadius)
    {
        // Bounce back
        sphereDirection = -sphereDirection;
    }
    // Keep the sphere on the checkerboard
    sphereX = fmaxf(-boardSize / 2.0f + sphereRadius, fminf(boardSize / 2.0f - sphereRadius, sphereX));
    sphereZ = fmaxf(-boardSize / 2.0f + sphereRadius, fminf(boardSize / 2.0f - sphereRadius, sphereZ));

    glutPostRedisplay();
}


// ROLLING feature
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
    glutTimerFunc(20, update, 0);
}

void updateT(int value)
{
    // Update torus rotation
    torusY -= torusSpeed * torusDirection;

    // Reverse the direction when the torus hits the top or bottom of the checkerboard
    if (torusY < torusRadius || torusY > boardSize / 2.0f - torusRadius)
    {
        torusDirection = -torusDirection;
    }

    glutPostRedisplay();
    glutTimerFunc(15, updateT, 0);
}

void updateC()
{
    angle += 0.5f; // Increment the rotation angle

    // Apply rotation and translation transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(cubeX, cubeY, cubeZ);
    glRotatef(angle, 1.0f, 1.0f, 1.0f); // Rotate the cube around (1, 1, 1) axis

    glutPostRedisplay(); // Trigger a redraw of the scene
}

void menu(int option)
{
    switch (option)
    {
    case 1:flag = 1; // Draw Torus
        break;
    case 2:flag = 0; // Draw Sphere
        break;
    case 3:flag = 2;  // Draw Cube
        break;
    case 4:flag = 3;  // Draw Wire Sphere
        break;
    case 5:flag = 4;  // Draw Wire Torus
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutCreateWindow("Solid Sphere on Checkerboard");
    glClearColor(1.0, .50, 0.0, 0.0);
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
    glutSpecialFunc(specialKeyboardCallback);

    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Torus", 1);
    glutAddMenuEntry("Draw Sphere", 2);
    glutAddMenuEntry("Draw Cube", 3);
    glutAddMenuEntry("Draw Wire Sphere", 4);
    glutAddMenuEntry("Draw Wire Torus", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutTimerFunc(0, update, 0);
    glutTimerFunc(0, updateT, 0);
    //glutTimerFunc(0, updateC, 0);

    glutMainLoop();

    return 0;
}
