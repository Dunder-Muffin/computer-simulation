#ifndef MAINPLOT_H
#define MAINPLOT_H

#include <algorithm>
#include <cmath>
#include <stack>
#include <sys/time.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <GL/glut.h>

//TODO: make const int instead or even enum to all constants
const int NUMBER_OF_STEPS = 25; /*maximum number of approximation steps*/
const double   A =-3;   /*size of the grid*/
const double  B =4;
const double  C =-3;
const double  D =4;
const int WIDTH = 300*abs(A)*abs(B); /*bind size of the window to the size of the grid (optional)*/
const int HEIGHT = 300*abs(D)*abs(C);
#define K 11 //N*N defines number of points in one cell

#define CELLS 2 /*defindes split of each side of cells*/
#define DELTA 0.25 //size of cell



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


std::string topologicalSort(double param_a, double param_b);

#endif // MAINPLOT_H
