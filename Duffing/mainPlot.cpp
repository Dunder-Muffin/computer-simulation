#include "mainPlot.h"
using namespace std;


int n = 1;

void keyboard (unsigned char key, int x, int y)
{
    if (key == ESCAPE)
        exit(0);
}

void skeyboard (int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        n++;
        if (n > NUMBER_OF_STEPS) n = NUMBER_OF_STEPS;
        glutPostRedisplay();
    }
//    else if (key == GLUT_KEY_DOWN)
//    {
//        n--;
//        if (n < 1) n = 1;
//        glutPostRedisplay();
//    }
}

Point start;           /*   Major flaw of C-library glut/freeglut  is  */
double t0;             /*   absence of argument line in display() function */
double dt;             /*   so we are forced to use a lot of global variables to implement an idea */

double rk_alpha;        /*  TODO: glut is depreciated; rewrite with QGLWidget */
double rk_beta;
double rk_gamma;
/////////////////////////////////////////////////////////userdeeifI'

double f(double x, double y, double t)
{
    return 0;//.5*cos(0.2 * t);
}
double dx (double x, double y, double t)
{
    return y;
}

double dy (double x, double y, double t)
{
    return -rk_alpha*y - rk_beta*x - rk_gamma * (x * x * x) + f(x,y,t);
}

void rk_dx (double &x, double y, double t)
{
    double k1 = dx(x, y, t);
    double k2 = dx (x + dt/2 * k1, y, t + dt/2);
    double k3 = dx (x + dt/2 * k2, y, t + dt/2);
    double k4 = dx( x + dt * k3, y, t + dt);

    x= x + dt/6 * (k1 + 2 * k2 + 2*k3 + k4);
}
void rk_dy (double x, double& y, double t)
{
    double k1 = dy(x, y, t);
    double k2 = dy (x, y + dt/2 * k1, t + dt/2);
    double k3 = dy (x, y + dt/2 * k2, t + dt/2);
    double k4 = dy(x, y + dt * k3, t + dt);

    y= y + dt/6 * (k1 + 2 * k2 + 2*k3 + k4);
}

void mapping (double &x, double &y)
{

    //glBegin(GL_LINES);
    //glVertex2f(start.x, start.y);
    //for (double tn = t0 + dt; tn <= NUMBER_OF_STEPS; tn += dt)
    {
        rk_dx(x, y, t0);
        rk_dy(x, y, t0);
      //  t0 += dt;

       // glVertex2f(x, y);
        //glEnd();
    }

}

int return_cell (double x, double y, int cols,  double delta)
{
    return (int)abs((double)(y - D)/delta) * cols + (int)abs((double)(x - A)/delta);
}

void interval (int cell, double& x1, double& y1, int cols, double delta)
{
    int row = cell / cols;
    int col = cell % cols;

    x1 = A + col * delta;

    y1 = D - row * delta;
}

vector <int> get_new_cells_from_old (int cell, int cols)
{
    vector <int> new_cells;

    //int row = cell / cols;
    //int col = cell % cols;
    int cols_old=cols/CELLS;
    int row_old = cell / cols_old;
    int col_old = cell % cols_old;

    row_old*=CELLS;
    col_old*=CELLS;

    int elem_0 = row_old*cols + col_old;

    new_cells.push_back(elem_0);
    new_cells.push_back(elem_0+1);
    new_cells.push_back(elem_0+cols);
    new_cells.push_back(elem_0+cols+1);
    return new_cells;
}
std::vector<bool> used;
std::vector<int> order;

void dfs1 (int v, vector<vector<int>> &grid) {
    used[v] = true;
    for (size_t i=0; i<grid[v].size(); ++i)
        if (!used[ grid[v][i] ])
            dfs1 (grid[v][i], grid);
    order.push_back (v);
}
 
void dfs2 (int v, vector<vector<int> > &gr, vector<int> &component) {
    used[v] = true;
    component.push_back (v);
    for (size_t i=0; i<gr[v].size(); ++i)
        if (!used[ gr[v][i] ])
            dfs2 (gr[v][i], gr, component);
}

vector<vector<int> > components;
void find_components (vector <vector<int> > &grid, vector<vector<int> > &gr, int number_of_cells)
{
    components.clear();
    vector<int> component;
    used.resize(number_of_cells);
    used.assign(number_of_cells, false);
    for (int i = 0; i < number_of_cells; i++)
        if (!used[i]) dfs1(i, grid);
    used.assign(number_of_cells, false);

    for (int i = 0; i < number_of_cells; i++)
    {
        int v = order[number_of_cells - 1 - i];
        if (!used[v])
        {
            dfs2(v, gr, component);
            if ((int)component.size() > 1)
            {
                components.push_back(component);
               // for(int it:gr[v])
                //if (find(vertices_to_iterate.begin(), vertices_to_iterate.end(), it) == vertices_to_iterate.end())
                //    vertices_to_iterate.push_back(it);
            }
            component.clear();
        }
    }

    order.clear();
}

void make_graph(vector<vector<int> > &graph, vector<vector<int> >& i_graph, int number_of_cells, double delta)
{
    int cols = (B - A) / delta;
    double lambda =delta/ (double)K;
if (n==1)
    for (int i = 0; i < number_of_cells; i++)
    {
        double x1, y1, x, y;
        interval(i, x1, y1, cols, delta);
//for (int k1 = 1; k1 <= K; k1++)
        for (int k = 1; k <= K; k++)
        {
            //for (int k1 = 1; k1 <= K; k1++)

                /*spawning dots inside of every cell
                 using such rule to left no cells ucovered
                 lose minimum of information    */
                x = x1 + k * lambda*2 - k * lambda;
                y = y1 + k * lambda - k * lambda*3;

                 mapping(x, y);

                if (x <= A || x >= B || y <= C || y >= D)
                    continue;

                int cell = return_cell(x , y, cols, delta);

                if (find(graph[i].begin(), graph[i].end(), cell) == graph[i].end())
                {

                    graph[i].push_back(cell);
                    i_graph[cell].push_back(i);

                }
        }
    }else
    {

    for (vector<int> component : components)
        for (int i_old: component)
        {

           vector<int >new_cells= get_new_cells_from_old (i_old,cols);
           for (int i : get_new_cells_from_old (i_old,cols))
           {

                double x1, y1, x, y;
                interval(i, x1, y1, cols, delta);

                for (int k = 1; k <= K; k++)
                {
                    //for (int k1 = 1; k1 <= K; k1++)

                        /*spawning dots inside of every cell
                         using such rule to left no cells ucovered
                         lose minimum of information    */
                        x = x1 + k * lambda*2 - k * lambda;
                        y = y1 + k * lambda - k * lambda*3;

                        mapping(x, y);

                        if (x <= A || x >= B || y <= C || y >= D)
                            continue;

                        int cell = return_cell(x , y, cols, delta);

                        if (find(graph[i].begin(), graph[i].end(), cell) == graph[i].end())
                        {
                            graph[i].push_back(cell);
                            i_graph[cell].push_back(i);

                        }
                }
        }
    }}
}

void approximation (int &scale, int &cols)
{
    double delta = DELTA;

    for (int i = 1; i < n; i++)
        delta /= CELLS;

    int rows = (D - C) / delta;
    cols = (B - A) / delta;
    int number_of_cells = rows * cols;

    scale = WIDTH* 2 / cols;
    vector <vector <int> > graph (number_of_cells);
    vector <vector <int> > i_graph (number_of_cells);

    make_graph(graph, i_graph, number_of_cells, delta);
    find_components(graph, i_graph, number_of_cells);
}

void draw_square (int cell, int scale,int cols)
{
    glColor3f(0.,0.,1.);
    int row = cell / cols;
    int col = cell % cols;
    glRectf(col * scale, row * scale, (col + 1) * scale, (row + 1) * scale);
}

void draw_grid(int scale)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    for (int i = 0; i < HEIGHT * 2; i+= scale)
    {
        glVertex2d(0, i);
        glVertex2d(WIDTH * 2, i);
    }

    for (int i = 0; i < WIDTH * 2; i+= scale)
    {
        glVertex2d(i, 0);
        glVertex2d(i, HEIGHT * 2);
    }

    glEnd();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw_grid();

    struct timeval t1, t2;


    int scale, cols;

    gettimeofday(&t1, NULL);
//                                    glBegin(GL_LINES);
//                                        glColor3f(1.0, 0.0, 0.0);
//                                        rungekutta();
//                                    glEnd();
//                                    glFlush();
        approximation(scale, cols);
    gettimeofday(&t2, NULL);
    for (vector<int> component : components)
        for (int v: component)
        {
            draw_square(v, scale, cols);
        }

    double t = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000;
/*    we can use here cols*cols due to square grid*/
    cout<<"Iter= "<<n<<"\tNum cells="<< cols*cols<< "\tT="<< t<<endl;

   // if (n < 7)// otherwise screen goes black of that many grid lines
    //draw_grid(scale);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2d(WIDTH, HEIGHT * 2);
        glVertex2d(WIDTH, 0);
        glVertex2d(WIDTH * 2, HEIGHT);
        glVertex2d(0, HEIGHT);
    glEnd();

    glFlush();
}

int plotWindowInit (int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    
    return 0;
}

int plotWindowOpen(double param_alpha, double param_beta, double param_gamma, Point starting_point, double param_t0, double param_dt)
{

    start = starting_point;
    t0 = param_t0;
    dt = param_dt;

    rk_alpha = param_alpha;
    rk_beta = param_beta;
    rk_gamma = param_gamma;
    glutCreateWindow("Symbol");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-6, 6, -3, 3, -1.0, 1.0);

    glOrtho(-WIDTH, WIDTH, HEIGHT, -HEIGHT, -1.0, 1.0);
    glTranslatef(-WIDTH, -HEIGHT, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutMainLoop();

    return 0;
}

