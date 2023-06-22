#include <GL/glut.h>
#include <cmath>

// Constants
const int windowWidth = 800;
const int windowHeight = 600;

void drawTorus(float innerRadius, float outerRadius, int sides, int rings) {
    // Calculate the step values
    float ringStep = 2.0f * M_PI / rings;
    float sideStep = 2.0f * M_PI / sides;

    // Draw the torus
    for (int i = 0; i < rings; i++) {
        float theta = i * ringStep;
        float nextTheta = (i + 1) * ringStep;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= sides; j++) {
            float phi = j * sideStep;
            float x = cos(theta) * (outerRadius + innerRadius * cos(phi));
            float y = sin(theta) * (outerRadius + innerRadius * cos(phi));
            float z = innerRadius * sin(phi);

            glVertex3f(x, y, z);

            x = cos(nextTheta) * (outerRadius + innerRadius * cos(phi));
            y = sin(nextTheta) * (outerRadius + innerRadius * cos(phi));
            z = innerRadius * sin(phi);

            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(45.0f, 1.0f, 1.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawTorus(0.5f, 1.5f, 30, 30);

    glutSwapBuffers();
}

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    float ratio = 1.0 * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL Torus Example");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
