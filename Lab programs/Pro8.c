#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416

void bino(int n, int *c)
{
	int k,j;
	for(k=0;k<=n;k++)
	{
		c[k]=1;
		for(j=n;j>=k+1;j--)
			c[k]*=j;
		for(j=n-k;j>=2;j--)
			c[k]/=j;
	}
}

void bezier(int *c, int cp[][2], int n)
{
	float x,y,u,blend;
	int k;
	
	glBegin(GL_POINTS);
	for(u=0; u<1.0; u+=0.01)
	{
		x=0;y=0;
		
		for(k=0;k<4;k++)
		{
			blend = c[k] * pow(u,k) * pow(1-u,n-k);
			x += cp[k][0] * blend;
			y += cp[k][1] * blend;
		}
		glVertex2f(x,y);
	}
	glEnd();
}


float theta = 0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int c[4],k,n=3;
	int cp[4][2] = {{100,400}, {150,450},{250,350},{300,400}};
	
	cp[1][0] += 50 * sin(theta*PI/180.0);
	cp[1][1] += 50 * sin(theta*PI/180.0);
	cp[2][0] -= 50 * sin((theta+30) * PI/180.0);
	cp[2][1] -= 50 * sin((theta+30) * PI/180.0);
	cp[3][0] += 50 * sin((theta) * PI/180.0);
	cp[3][1] += 50 * sin((theta) * PI/180.0);
	
	theta += 10.0;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glPointSize(5);
	
	bino(n,c);
	
	glPushMatrix();
	glLineWidth(5);

	glColor3f(1.0,0.4,0.2);
	for(int i = 0; i < 50; i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(c,cp,n);
	}
	
	glColor3f(1,1,1);
	for(int i = 0; i<50; i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(c,cp,n);
	}
	
	glColor3f(0,1,0);
	for(int i = 0; i<50; i++)
	{
		glTranslatef(0,-0.8,0);
		bezier(c,cp,n);
	}
	
	glPopMatrix();
	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	
	glBegin(GL_LINES);
	glVertex2f(100,400);
	glVertex2f(100,40);
	
	glEnd();
	
	glutPostRedisplay();
	glutSwapBuffers();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	
	glutCreateWindow("Bezier Curve");
	init();
	
	glutDisplayFunc(display);
	glutMainLoop();
	
}
