//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctime>
#include <iostream>
using namespace std;
#define ESCAPE '\033'
#define N 		1000
float time1, time2;
float CLK_TCK;

GLint WIDTH = 1000, HEIGHT = 800;

double a=0;

double x0 = 1;
double y_0 = 1;
double t0 = 0;
double dt = 10.0 / N;


double dx (double x, double y, double t)
{
    return y;
}

double dy (double x, double y, double t)
{
    return (-0.25)*y + 0.5*x - 0.5 * (x * x * x) + a*cos(0.2 * t);
}

float e_dx (double x, double y, double t)
{
    return x + dt*dx(x,y,t);
}
float e_dy (double x, double y, double t)
{
    return y + dt*dy(x,y,t);
}

void Euler (double x0, double y0, double t0)
{
    double x = x0;
    double y = y0;
    double t = t0;
    
    glVertex2f(x, y);
    for (double tn = t + dt; tn <= 1000; tn += dt) 
    {
        float xn = e_dx(x, y, t);
        float yn = e_dy(x, y, t);
        t = tn;
                
        x = xn;
        y = yn;
        glVertex2f(xn, yn);
    }
    
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 
 
    glColor3f(0.0, 0.0, 0.0); 
    glBegin(GL_LINES);   
		glVertex2f(-WIDTH, 0);   
		glVertex2f(WIDTH, 0);   
    glEnd();
 
    glBegin(GL_LINES);
		glVertex2f(0, HEIGHT);
		glVertex2f(0, -HEIGHT);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.0, 0.0);		//red
		Euler(x0, y_0, t0);
    glEnd();
    glFlush();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == ESCAPE)
        exit(0);
}
 
int main(int argc, char** argv)
{
    time1 = clock();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Euler");
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int orthoW = a? 6 : 3;
    int orthoH = a? 3 : 2;
    glOrtho(-orthoW, orthoW, -orthoH, orthoH , -1.0, 1.0);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyboard);
    time2 = clock();
    cout<<(time2-time1)/CLOCKS_PER_SEC<<endl;
    glutMainLoop();
    
    return 0;
}
