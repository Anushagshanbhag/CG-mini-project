#include <GL/glut.h>
#include <vector>
#include <cmath>

void drawTorus(float R, float r, int N, int M) {
    std::vector<float> vertices;
    std::vector<float> normals;

    for (int i = 0; i <= N; i++) {
        float theta = i * 2 * M_PI / N;
        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        for (int j = 0; j <= M; j++) {
            float phi = j * 2 * M_PI / M;
            float cosPhi = std::cos(phi);
            float sinPhi = std::sin(phi);

            float x = (R + r * cosTheta) * cosPhi;
            float y = (R + r * cosTheta) * sinPhi;
            float z = r * sinTheta;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            float nx = cosTheta * cosPhi;
            float ny = cosTheta * sinPhi;
            float nz = sinTheta;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);
        }
    }

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            int k = i * (M + 1) + j;
            glNormal3f(normals[3 * k], normals[3 * k + 1], normals[3 * k + 2]);
            glVertex3f(vertices[3 * k], vertices[3 * k + 1], vertices[3 * k + 2]);

            k = (i + 1) * (M + 1) + j;
            glNormal3f(normals[3 * k], normals[3 * k + 1], normals[3 * k + 2]);
            glVertex3f(vertices[3 * k], vertices[3 * k + 1], vertices[3 * k + 2]);
        }
    }
    glEnd();
}