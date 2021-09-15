#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/freeglut.h>
using namespace std;
float X0=0, Y0=0, x=0, y=0;
void setNewCoordSystem(int width, int height, int internalWidth, int internalHeight)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-internalWidth, internalWidth, -internalHeight, internalHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display()
{ 	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(0.5); 
	glColor3f(0, 0, 0); 
	glBegin(GL_LINES); 
		glVertex2f(-2, 0);
		glVertex2f(2, 0);
		glVertex2f(0, 1);
		glVertex2f(0, -1);
		//засечки
		glVertex2f(-0.06, 0.3); // по у
		glVertex2f(0.06, 0.3);

		glVertex2f(-0.06, -0.3); // по -у
		glVertex2f(0.06, -0.3);


		glVertex2f(1.28, -0.06); // по х
		glVertex2f(1.28, 0.06);

		glVertex2f(-1.28, -0.06); // по -х
		glVertex2f(-1.28, 0.06);

		glEnd();
		glPointSize(0.7);
       glColor3f(1.0f,0.0f,0.0f);
       
       glBegin(GL_POINTS);
       for(int i=0; i<100000; i++)
       {
       	x = X0;
       	y = Y0;
       	X0 = 1-1.4*x*x+y;
       	Y0 = 0.3*x;
       	glVertex2f(x, y);
       }  		 
	     glEnd();
	     glutSwapBuffers();
	     glFinish();
	   }
   void processNormalKeys(unsigned char key, int xx, int yy)
   {
   	if (key==27)
   		exit(0);
   }

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 800);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Henon");
	glClearColor(1.0,1.0,1.0,1.0);
	setNewCoordSystem(800, 600, 2, 1);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;
}
