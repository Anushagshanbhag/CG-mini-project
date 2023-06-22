#include <stdio.h>
#include <GL/glut.h>

// Constants
#define WIDTH 800
#define HEIGHT 600

// Torus parameters
#define RADIUS 0.5f
#define TUBE_RADIUS 0.2f
#define SLICES 50
#define STACKS 50

// Initialization
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glMatrixMode(GL_MODELVIEW); // Set the matrix mode to ModelView
    glLoadIdentity(); // Reset the model-view matrix

    // Set the camera position
    gluLookAt(0.0f, 0.0f, 3.0f, // Eye position
              0.0f, 0.0f, 0.0f, // Look-at position
              0.0f, 1.0f, 0.0f); // Up direction

    glColor3f(1.0f, 1.0f, 1.0f); // Set the drawing color to white

    // Draw the torus
    glutWireTorus(RADIUS, TUBE_RADIUS, SLICES, STACKS);

    glFlush(); // Flush the OpenGL buffers
    glutSwapBuffers(); // Swap the front and back buffers (double buffering)
}

// Reshape callback
void reshape(int width, int height) {
    glViewport(0, 0, width, height); // Set the viewport dimensions

    glMatrixMode(GL_PROJECTION); // Set the matrix mode to Projection
    glLoadIdentity(); // Reset the projection matrix

    // Set the perspective projection
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffering, RGB color, and depth testing
    glutInitWindowSize(WIDTH, HEIGHT); // Set the window size
    glutCreateWindow("OpenGL Torus"); // Create a window with the specified title

    init(); // Initialize OpenGL

    glutDisplayFunc(display); // Register the display callback function
    glutReshapeFunc(reshape); // Register the reshape callback function

    glutMainLoop(); // Enter the main loop

    return 0;
}