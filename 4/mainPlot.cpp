#include "mainPlot.h"
using namespace std;


int n = 1;
double a, b;

void keyboard (unsigned char key, int x, int y)
{
    if (key == '\033')
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
    else if (key == GLUT_KEY_DOWN)
    {
        n--;
        if (n < 1) n = 1;
        glutPostRedisplay();
    }
}


void mapping (double &xn, double &yn)
{
    //const double a = 0.28;
    //const double b = 0.0113;
    double x = xn;
    double y = yn;

    xn = (x * x) - (y * y) + a;
    yn = 2 * x * y + b;
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


vector<vector<int> > find_components (vector <vector<int> > &grid, vector<vector<int> > &gr, int number_of_cells)
{
    vector<vector<int> > components;
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
            }
            component.clear();
        }
    }
/*
    for (vector<int>comp : components)
    {
        for (int i : comp)
        {
            cout << i << " ";
        }
        cout << endl;
    }*/
    order.clear();
    return components;
}

void make_graph(vector<vector<int> > &graph, vector<vector<int> >& i_graph, int number_of_cells, double delta)
{
    int cols = (B - A) / delta;
    double lambda =delta/ (double)K;

    for (int i = 0; i < number_of_cells; i++)
    {
        double x1, y1, x, y;
        interval(i, x1, y1, cols, delta);
        //cout << i << endl;
        //cout << "x1 = "<< x1 << " y1 = "<< y1;

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
                    /*TODO: find out why these two push_backs consume 66% time*/
                    graph[i].push_back(cell);
                    i_graph[cell].push_back(i);

                }

        }

        //cout << endl;
    }

}

vector<vector<int> > approximation (int &scale, int &cols)
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

    return find_components(graph, i_graph, number_of_cells);
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
    vector<vector<int> > components = approximation(scale, cols);
    gettimeofday(&t2, NULL);
    for (vector<int> component : components)
        for (int v: component)
        {
            draw_square(v, scale, cols);
        }
    

    double t = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000;
/*    we can use here cols*cols due to square grid*/
    cout<<"Iter= "<<n<<"\tNum cells="<< cols*cols<< "\tT="<< t<<endl;

    if (n < 7)// otherwise screen goes black of that many grid lines
    draw_grid(scale);

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

int plotWindowOpen(double param_a, double param_b)
{
    a = param_a;
    b = param_b;

    glutCreateWindow("Symbol");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH, WIDTH, HEIGHT, -HEIGHT, -1.0, 1.0);
    glTranslatef(-WIDTH, -HEIGHT, 0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutMainLoop();

    return 0;
}

