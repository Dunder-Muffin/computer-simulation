#ifndef MAINPLOT_H
#define MAINPLOT_H

#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <GL/glut.h>

//TODO: make const int instead or even enum to all constants
const int NUMBER_OF_STEPS = 50;
const double DELTA = 0.1; //initial distance between two neighboring points
const int WIDTH = 1200;
const int HEIGHT = 800;

#define DELTA_STEP 0.1 /*multiplier of DELTA on each step*/

struct Point
{
    double x,y;
bool operator==(const Point& rhs){ return this->x==rhs.x&&this->y==rhs.y; }
};

double dist(Point dot1, Point dot2);

void keyboard (unsigned char key,int x, int y);


void skeyboard (int key,int x, int y);

Point mapping (Point o);

void draw_dots();

void approximation (std::vector<Point> dots);

void display();

int plotWindowInit (int argc, char* argv[]);

int plotWindowOpen(double param_a, std::vector<Point> &init_dots, std::vector<Point>& init_dots_reversed);

#endif // MAINPLOT_H
