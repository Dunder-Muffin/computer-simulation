#ifndef MAINPLOT_H
#define MAINPLOT_H

#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <GL/glut.h>

//TODO: make const int instead or even enum to all constants
const int NUMBER_OF_STEPS = 1000; /*maximum number of approximation steps*/
const double   A =-10;   /*size of the grid*/
const double  B =10;
const double  C =-10;
const double  D =10;
const int WIDTH = 300*abs(A)*abs(B); /*bind size of the window to the size of the grid (optional)*/
const int HEIGHT = 300*abs(D)*abs(C);
#define K 11 //N*N defines number of points in one cell

#define CELLS 2 /*defindes split of each side of cells*/

#define DELTA 2 //size of cell

#define ESCAPE '\033'

struct Point
{
    double x,y;
bool operator==(const Point& rhs){ return this->x==rhs.x&&this->y==rhs.y; }
//Point &operator=(const Point& rhs){ x=rhs.x; y=rhs.y; return *this; }
};
void keyboard (unsigned char key, int x, int y);


void skeyboard (int key, int x, int y);

int return_cell (double x, double y, int cols,  double delta);
std::vector <int> get_new_cells_from_old (int cell, int cols);
void interval (int cell, double& x1, double& y1, int cols, double delta);

void dfs1 (int v, std::vector<std::vector<int>> &grid);
void dfs2 (int v, std::vector<std::vector<int> > &gr, std::vector<int> &component);

void find_components (std::vector <std::vector<int> > &grid, std::vector<std::vector<int> > &gr, int number_of_cells);

void make_graph(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> >& i_graph, int number_of_cells, double delta,std::vector<std::vector<int> >& components);

void approximation (int &scale, int &cols, std::vector<std::vector<int> >& components);

void draw_grid(int scale);

void display();

int plotWindowInit (int argc, char* argv[]);

int plotWindowOpen(double param_alpha, double param_beta, double param_gamma, Point starting_point, double t0, double param_dt);

#endif // MAINPLOT_H
