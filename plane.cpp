#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<string>

bool runprop = false;

GLfloat r2 = 0.0;

std::string projectName ="3D Plane Viewer";
std::string instructions="Instructions";
std::string rules ="Keyboard Interactions: Press X,Y,Z to move along +ve x y z axis and x,y,z to move along -ve x y z axis.";
std::string mousee = "Mouse Interactions: Left Click and middle Buttton to change the axis of rotation.";
std::string menuu = "Menu Interactions: Right click to start, stop the propeller and exit.";
std::string by = "Project By Melvita And Krithika";


void Plane(){

// Main Body
glPushMatrix();
glScalef(.3,0.3,1.5);//Scaling 0.3 to x axis 0.3 to y axis 1.5 to z axis
glColor3f(0.5,0.5,0.5);
glutSolidSphere(2.0,50,50);//2 units of radius subdivisions of 50 50 v h
glPopMatrix();//to retrieve the the transformation

glPushMatrix();
glTranslatef(0.0,0.1,-1.8);//moves 0.0 x 0.1 y 0
glScalef(1.0,1,1.5);
glColor3f(0,0,1);
glutSolidSphere(0.5,25,25);
glPopMatrix();

//Left Fin
glPushMatrix();
glTranslatef(-1.0,0,0);
glScalef(1.5,0.1,0.5);
glColor3f(0,0,0);
glutSolidSphere(1.0,50,50);
glPopMatrix();

// Right Fin
glPushMatrix();
glTranslatef(1.0,0,0);
glScalef(1.5,0.1,0.5);
glColor3f(0,0,0);
glutSolidSphere(1.0,50,50);
glPopMatrix();

//right Tail fin
glPushMatrix();
glTranslatef(0.8,0,2.4);
glScalef(1.2,0.1,0.5);
glColor3f(0.0,0,0);
glutSolidSphere(0.4,50,50);
glPopMatrix();

//left Tail fin
glPushMatrix();
glTranslatef(-0.8,0,2.4);
glScalef(1.2,0.1,0.5);
glColor3f(0.0,0,0);
glutSolidSphere(0.4,50,50);
glPopMatrix();

//Top tail fin
glPushMatrix();
glTranslatef(0,0.5,2.4);
glScalef(0.1,1.1,0.5);
glColor3f(0.0,0,0);
glutSolidSphere(0.4,50,50);
glPopMatrix();

// Blades
glPushMatrix();
glRotatef(r2,0.0,0.0,1.0);
glPushMatrix();
glTranslatef(0,0.0,-3.0);
glScalef(1.5,0.2,0.1);
glColor3f(0.0,0,0);
glutSolidSphere(0.3,50,50);
glPopMatrix();



//Front wheel
glPushMatrix();
glTranslatef(0.0,-0.8,-1.5);
glRotatef(90,0.0,1,0);// angle of rotation 90 degree rotation on y axis
glScaled(0.3,0.3,0.3);
glutSolidTorus(0.18,0.5,25,25);//radius of tube,radius of entire torus,number of sides, no. of divisions
glColor3f(1,1,1);
glutSolidTorus(0.2,0.1,25,25);

glPopMatrix();
glPushMatrix();
glTranslatef(0.0,-0.4,-1.5);
glRotatef(20,0.0,1,0);
glScaled(0.05,0.3,0.05);
glutSolidSphere(1.0,25,25);
glPopMatrix();

//Rear wheel
glPushMatrix();
glTranslatef(0.3,-0.8,0.7);
glRotatef(90,0.0,1,0);
glScaled(0.3,0.3,0.3);
glColor3f(0,0,0);
glutSolidTorus(0.18,0.5,25,25);
glColor3f(1,1,1);
glutSolidTorus(0.2,0.1,25,25);
glPopMatrix();

glPushMatrix();
glTranslatef(0.3,-0.4,0.7);
glRotatef(20,0.0,1,0);
glScaled(0.05,0.3,0.05);
glutSolidSphere(1.0,25,25);
glPopMatrix();

//rear 2 wheel
glPushMatrix();
glTranslatef(-0.3,-0.8,0.7);
glRotatef(90,0.0,1,0);
glScaled(0.3,0.3,0.3);
glColor3f(0,0,0);
glutSolidTorus(0.18,0.5,25,25);
glColor3f(1,1,1);
glutSolidTorus(0.2,0.1,25,25);
glPopMatrix();

glPushMatrix();
glTranslatef(-0.3,-0.4,0.7);
glRotatef(20,0.0,1,0);
glScaled(0.05,0.3,0.05);
glutSolidSphere(1.0,25,25);
glPopMatrix();
}
void moveprop(int value) {
    if (runprop) {
       r2 += 50.0f; // Adjust the rotation speed as needed
        glutPostRedisplay();// redraws
    }

    glutTimerFunc(25, moveprop, 0);//move function is called again and again after 25ms
}
/*
void Move(int value)
{
    r2 += 5.0;  // Adjust the rotation speed as desired
    if (r2 > 360.0)//if r2 exceeds 360 then subtract r2 from 360
        r2 -= 360.0;

    glutPostRedisplay();  // Request redrawing of the scene

    // Register the timer function again
    glutTimerFunc(50, Move, 0);//move function is called again and again after 50 ms
}
*/

GLfloat theta[] = {0.0,0.0,0.0}; GLint axis = 2;
GLdouble viewer[]= {0.0, 0.0, 5.0}; // initial viewer location camera pos x y z


void display(void)
{
    //light properties and material properties

   GLfloat ambient[] = { 0.7, 0.7, 0.7, 1.0 };//material properties light which falls equally on all surface r,g,b,alpha
   GLfloat diffuse[] = { 0.2, 0.2, 0.2, 1.0 };//amount of shading r,g,b,alpha
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };//points on a surface where entire light is reflected back
   GLfloat shininess[] = { 50.0 };//size of white highlights

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

   GLfloat lightIntensity[]={0.1f,0.1f,0.1f,1.0f};
   GLfloat light_position[]={1.0f,1.0f,1.0f,0.0f};

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, lightIntensity);
   //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
 // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glClearColor(0.0,0.0,0.0,0.0);
 glLoadIdentity();
 gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//set camera pos x y z viewer,point,upvector of camera
 glRotatef(theta[0], 1.0, 0.0, 0.0);//x
 glRotatef(theta[1], 0.0, 1.0, 0.0);//y
 glRotatef(theta[2], 0.0, 0.0, 1.0);//z

        Plane();
 glFlush();//display contents from buffer
 glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
     if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     axis = 0;
     if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
     axis = 1;
     //if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
     //axis = 2;
     theta[axis] += 2.0;
     if( theta[axis] > 360.0 )
     theta[axis] -= 360.0;
     display();
}
void renderText(float x, float y, void *font, const std::string &text) {
    glRasterPos2f(x, y);
    for (const char &c : text) {
        glutBitmapCharacter(font, c);
    }
}

void keys(unsigned char key, int x, int y)
{
 if(key == 'x')
 viewer[0]-= 1.0;//l
 if(key == 'X')
 viewer[0]+= 1.0;//r
 if(key == 'y')
 viewer[1]-= 1.0;//d
if(key == 'Y')
 viewer[1]+= 1.0;//u
 if(key == 'z')
 viewer[2]-= 1.0;//far
 if(key == 'Z')
 viewer[2]+= 1.0;//near
display();
}


void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 if(w<=h)
 glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 2.0* (GLfloat) h /(GLfloat) w,2.0, 20.0);//ymin,ymax,zmin,near ,far
 else
 glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);
 glMatrixMode(GL_MODELVIEW);
}

void display2(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render project name
    glColor3f(1.0f, 0.0f, 0.0f); // Set text color to white
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1); // orthographic projection for text 0 0 bt lft 1 1 tp rt
    renderText(0.05f, 0.95f, GLUT_BITMAP_HELVETICA_18, projectName);//font style sixe
     renderText(0.05f, 0.8f, GLUT_BITMAP_HELVETICA_18, instructions);
     renderText(0.05f, 0.5f, GLUT_BITMAP_HELVETICA_18, mousee);

        renderText(0.05f, 0.6f, GLUT_BITMAP_HELVETICA_18, menuu);
    renderText(0.05f, 0.7f, GLUT_BITMAP_HELVETICA_18, rules);
      renderText(0.6f, 0.4f, GLUT_BITMAP_HELVETICA_18, by);
    glutSwapBuffers();
}
/*
void menu(int option){
if(option ==1){
    glClearColor(0.1,0.0,0.1,0.0);

}
if(option==2){
    glClearColor(0.1,0.1,0.0,0.0);}
    if(option ==3){
        glClearColor(0.0,0.1,0.1,0.0);

}
}*/
void menu(int choice) {
    switch (choice) {
        case 1:
            runprop = true;
            break;
        case 2:
            runprop = false;
            break;
        case 3:
            exit(0);
            break;
    }
}
void createMenu() {
    glutCreateMenu(menu);
    glutAddMenuEntry("Start Propeller", 1);
    glutAddMenuEntry("Stop Propeller", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
 glutInitWindowPosition(800, 100);
  // First window
 glutCreateWindow("3D Plane Viewer Output Window");
 glutReshapeFunc(myReshape);
 glutDisplayFunc(display);
 glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
 glutMouseFunc(mouse);
 glutKeyboardFunc(keys);
 createMenu();
 glutKeyboardFunc(keys);
 glEnable(GL_DEPTH_TEST);//hidden surface removing
 glutTimerFunc(25, moveprop, 0);
 //second Window
 glutInitWindowSize(700, 500);
  glutInitWindowPosition(100, 100);
    glutCreateWindow("Instruction Window");
    glutDisplayFunc(display2);
 glutMainLoop();
}