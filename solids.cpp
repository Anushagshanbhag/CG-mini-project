#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
float angle = 0.0f;
GLfloat torusRotation = 0.0f;
int width = 800;  // Window width
int height = 600;
static int slices = 16;
static int stacks = 16;

int rotationFlag = 1;
int wireframeFlag = 0;
int lightingFlag = 1;

int currentSolid = 1;

void drawSolidCylinder()
{
    float radius = 1.0f;
    float height = 2.0f;
    float angle;
    float x, y, z;
    float stackHeight = height / stacks;
    float stackRadius = radius / stacks;

    // Draw sides
     for (int i = 0; i < stacks; i++)
    {
        float stackTop = height / 2 - i * stackHeight;
        float stackBottom = stackTop - stackHeight;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++)
        {
            angle = 2.0 * 3.14159 * j / slices;
            x = radius * cos(angle);
            y = radius * sin(angle);
            z = stackTop;

            glNormal3f(cos(angle), sin(angle), 0.0);
            glVertex3f(x, y, z);

            glNormal3f(cos(angle), sin(angle), 0.0);
            glVertex3f(x, y, stackBottom);
        }
        glEnd();
    }
}

void drawSolidDisk()
{
    float radius = 1.0f;
    float angle;
    float x, z;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Center vertex
    for (angle = 0.0f; angle <= 2.0f * M_PI + 0.01f; angle += (2.0f * M_PI / slices))
    {
        x = radius * sin(angle);
        z = radius * cos(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 80.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslated(-2.4, 1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
    if (currentSolid == 2)
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        drawSolidCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2, -7);
    glRotated(60, 1, 1, 1);
    glRotated(a, 1, 1, 1);
    glColor3f(1.0,1.0,1.0);
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
       glutSolidCone(1.0, 2.0, 50, 50);

    glPopMatrix();

    glPushMatrix();
    glTranslated(2.9, 1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        glutSolidTorus(0.4, 1, 30, 30);

    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, -1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        drawSolidDisk();

    glPopMatrix();

     glPushMatrix();
    glTranslated(-1.5, -1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        glutSolidSphere(1.0, 50, 50);
    glPopMatrix();
    }
    if (currentSolid == 3)
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        drawSolidCylinder();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2, -7);
    glRotated(60, 1, 1, 1);
    glRotated(a, 1, 1, 1);
    glColor3f(1.0,1.0,1.0);
    if (currentSolid == 4)
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
       glutSolidCone(1.0, 2.0, 50, 50);

    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.9, 1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
    if (currentSolid ==5 )
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        glutSolidTorus(0.4, 1, 30, 30);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, -1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
    if (currentSolid == 6)
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        drawSolidDisk();
    }
    glPopMatrix();

     glPushMatrix();
    glTranslated(-1.5, -1.2, -7);
    glRotated(60, 1, 0, 0);
    glRotated(a, 1, 1, 1);
    if (currentSolid == 7)
    {
        if (wireframeFlag)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (lightingFlag)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        glutSolidSphere(1.0, 50, 50);
    }
    glPopMatrix();

    glutSwapBuffers();
}

static void menu(int value)
{
    switch (value)
    {
    case 1:
        currentSolid = 1;
        break;

    case 2:
        currentSolid = 2; // All Solids
        break;
    case 3:
        currentSolid = 3; // Cylinder
        break;
    case 4:
        currentSolid = 4; // Cone
        break;
    case 5:
        currentSolid = 5; // Torus
        break;
    case 6:
        currentSolid = 6; // Disc
        break;
    case 7:
        currentSolid = 7; // Sphere
        break;
    case 8:
        wireframeFlag = !wireframeFlag; // Toggle wireframe mode
        break;
    case 9:
        lightingFlag = !lightingFlag; // Toggle lighting
        break;
    case 10:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

static void createMenu()
{
    int solidMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Olympic Ring", 1);
    glutAddMenuEntry("Solids", 2);
    glutAddMenuEntry("Cylinder", 3);
    glutAddMenuEntry("Cone", 4);
    glutAddMenuEntry("Torus", 5);
    glutAddMenuEntry("Disk", 6);
    glutAddMenuEntry("Sphere", 7);

    int optionsMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Wireframe", 8);
    glutAddMenuEntry("Toggle Lighting", 9);

    glutCreateMenu(menu);
    glutAddSubMenu("Solids", solidMenu);
    glutAddSubMenu("Options", optionsMenu);
    glutAddMenuEntry("Quit", 10);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

static void idle(void)
{
    glutPostRedisplay();
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Solid Objects");
    createMenu();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_diffuse[] = { 2.0, 1.7, 0.5, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

}


