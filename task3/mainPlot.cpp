#include "mainPlot.h"
using namespace std;


int n = 1;
double a, b;



void mapping (double &xn, double &yn)
{

    double x = xn;
    double y = yn;
    double tau = 0.4 - 6/(1+x*x+y*y);

    xn = 1.04 + (-0.9)*(x*cos(tau)-y*sin(tau)); //(x * x) - (y * y) + a;
    yn = 1.2*(x*sin(tau)+y*cos(tau));
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
std::vector<int> used;
std::vector<int> order;
stack <int> task;
//void dfs1 (int v, vector<vector<int>> &grid) {
//    task=stack<int>();
//    task.push(v);

//    while(!task.empty())
//    {
//        int i =task.top();
//        task.pop();

//        // for (auto k =grid[29].begin();k<grid[29].end();k++)
//            // cout<<*k<<endl;
//         //for (vector<int>::iterator j =grid[i].begin();j!=grid[i].end();j++)
//        for (size_t j=0; j<grid[i].size(); ++j)
//            if (!used[grid[i][j] ]){
//                task.push (grid[i][j]);
//        used[grid[i][j] ] = true;
//        order.push_back (grid[i][j] );
//            }
//        if (!used[i])
//        {
//        used[i] = true;
//        order.push_back (i);
//        }
//    }
//     order.push_back (0);
//}
stack <int> forgotten;
//void dfs1 (int v, vector<vector<int>> &grid)
//{
//    int uu;
//task=stack<int>();
//std::vector<uint> childsVisited(100000);
//void dfs1(int s,vector<vector<int>> &g)
//{
//   // used= vector<int>();
//    stack<int> stk;
//    stk.push(s);
//    used[s] = 1;

//    int jumpOut, count;

//    int counter = 0;
//    while(!stk.empty())
//    {
//        jumpOut = 0;
//        int cur = stk.top();
//        for ( ;childsVisited[cur] < g[cur].size(); ++childsVisited[cur] )
//        {
//            int i = childsVisited[cur];
//            int next = g[cur][i];
//            if(used[next] != 1)
//            {
//                stk.push(next);
//                used[next] = 1;

//                jumpOut = 1; //Jump to the while loop's beginning
//                break;
//            }
//        }

//        if(jumpOut == 0)
//            order.push_back(stk.top());
//            stk.pop();
//    }
//}
//    task.push(v);
//     while(!task.empty()){
//        uu =task.top();
//         task.pop();

//        if (used[uu] != true){
//            used[uu]= true;
//            order.push_back(uu);//print(uu.data)
//            for (vector<int>::iterator vv =grid[uu].begin();vv!=grid[uu].end();vv++)
//                task.push(*vv);
//        }
//}order.push_back (0);}
void dfs1 (int v, vector<vector<int>> &grid) {
    task=stack<int>();
    task.push(v);
    bool hasUnusedNeighbours;
    int i ;//=task.top();

    while(!task.empty())
    {
        i =task.top();
       //used[i] = true;
        // for (auto k =grid[29].begin();k<grid[29].end();k++)
            // cout<<*k<<endl;
         //for (vector<int>::reverse_iterator j =grid[i].rbegin();j!=grid[i].rend();j++)
        hasUnusedNeighbours=false;
        for (size_t j=grid[i].size()-1; j<=0; --j)
            if (!used[ grid[i][j] ]){
                hasUnusedNeighbours=true;
                task.push (grid[i][j]);
                //used[grid[i][j]] = true;
            }
        if (!hasUnusedNeighbours)
        {
            used[i] = true;
            task.pop();
            order.push_back (i);

//            order.push_back (i);
//            if (!forgotten.empty()&&нет братьев)
//            {
//                i=forgotten.top();
//                forgotten.pop();
//            }
//            else
//            {
//                i =task.top();
//                task.pop();
//            }
        }
        else
        {

//         forgotten.push(i);
//         i =task.top();
//         task.pop();
//        }
    }
//  }   //order.push_back (0);
}}
//void dfs1 (int v, vector<vector<int>> &grid) {

//    used[v] = true;
//    for (size_t i=0; i<grid[v].size(); ++i)
//        if (!used[ grid[v][i] ])
//            dfs1 (grid[v][i], grid);
//    order.push_back (v);
//}
int counter=0;
void make_graph(vector<vector<int> > &graph, int number_of_cells, double delta)
{
    int cols = (B - A) / delta;
    double lambda =delta/ (double)K;
if (n==1)
    for (int i = 0; i < number_of_cells; i++)
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
                }
        }
    }
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


    graph.clear();
    used.clear();
    order.clear();


    make_graph(graph, number_of_cells, delta);
    used.resize(number_of_cells);
    used.assign(number_of_cells, false);
    for (int i = 0; i < number_of_cells; i++)
        if (!used[i]) dfs1(i, graph);
}


std::string topologicalSort(double param_a, double param_b)
{


    a = param_a;
    b = param_b;

    struct timeval t1, t2;

    int scale, cols;

    gettimeofday(&t1, NULL);
        approximation(scale, cols);
    gettimeofday(&t2, NULL);

    double t = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000;
/*    we can use here cols*cols due to square grid*/
//    cout<<"Iter= "<<n<<"\tNum cells=\
//"<< cols*cols<< "\tT="<< t<<"\tV= "<<counter<<endl;

    std::ostringstream oss;

    if (!order.empty())
    {
      // Convert all but the last element to avoid a trailing ","
      std::copy(order.begin(), order.end()-1,
          std::ostream_iterator<int>(oss, ", "));

      // Now add the last element with no delimiter
      oss << order.back();
    }
    return oss.str();
}

