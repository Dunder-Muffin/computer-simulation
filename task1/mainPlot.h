#ifndef MAINPLOT_H
#define MAINPLOT_H

#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <GL/glut.h>

#define WIDTH 1200
#define HEIGHT 800
const int NUMBER_OF_STEPS = 7;
const double   A =-1.5;             //TODO: make const int instead of define or even enum
const double  B =1.5;
const double  C =-1;
const double  D =1;

#define K 1000 //number of points in one cell

#define CELLS 2

#define DELTA 0.25 //size of cell



void keyboard (unsigned char key, int x, int y);


void skeyboard (int key, int x, int y);


void henon (double &xn, double &yn);


int return_cell (double x, double y, int cols,  double delta);

void interval (int cell, double& x1, double& y1, int cols, double delta);

void dfs1 (int v, std::vector<std::vector<int>> &grid);
void dfs2 (int v, std::vector<std::vector<int> > &gr, std::vector<int> &component);

std::vector<std::vector<int> > find_components (std::vector <std::vector<int> > &grid, std::vector<std::vector<int> > &gr, int number_of_cells);

void make_graph(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> >& i_graph, int number_of_cells, double delta);

std::vector<std::vector<int> > approximation (int &scale, int &cols);

void draw_grid(int scale);

void display();

int plotWindowInit (int argc, char* argv[]);

int plotWindowOpen(double param_a, double param_b);

#endif // MAINPLOT_H
