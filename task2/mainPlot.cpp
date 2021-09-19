#include "mainPlot.h"
using namespace std;

double a;
//////////////////THIS FUNCTION IS USER-DEFINED///////////////////////
Point mapping_straight(Point o)
{
   Point image;
   image.x  = o.x + o.y+ a *o.x* (1-o.x *o.x);
   image.y = o.y+ a*o.x*(1-o.x*o.x) ;
   return image;
}
Point mapping_reversed(Point o)
{
   Point image;
   double  d= o.x - o.y;
   image.x  = d;
   image.y = o.y - a* d *(1-d*d);
   return image;
}
////////////////////////////////////////////////////////////////////
int n = 1;

std::vector<Point> dots;
std::vector<Point> dots_reversed;

void keyboard (unsigned char key,int x, int y)
{
    if (key == '\033')
        exit(0);
}

void skeyboard (int key,int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        n++;
        if (n > NUMBER_OF_STEPS) n = NUMBER_OF_STEPS;
        glutPostRedisplay();
    }
}

double dist(Point dot1, Point dot2)
{
    double dist_x = dot2.x - dot1.x;
    double dist_y = dot2.y - dot1.y;
    return sqrt(dist_x * dist_x + dist_y * dist_y);
}

void throw_new_points(Point dot1, Point dot2, std::vector<Point> &new_dots,Point (*mapping)(Point o))
{
    Point middle_dot = {(dot1.x + dot2.x) / 2, (dot1.y + dot2.y) / 2};

    Point new_dot1 = mapping(dot1);
    Point new_dot2 = mapping(dot2);
    double distance = dist(new_dot1, new_dot2);
    if (distance > DELTA)
    {
        throw_new_points(dot1, middle_dot, new_dots, mapping);
        throw_new_points(middle_dot, dot2, new_dots, mapping);
    }else
    {
        if (find(new_dots.begin(), new_dots.end(), new_dot1 ) != new_dots.end())
            new_dots.push_back(new_dot2);
        else
        {
            new_dots.push_back(new_dot1);
            new_dots.push_back(new_dot2);
        }
    }
}

void approximation ()
{
  vector<Point> new_dots;

  for (auto it =dots.begin();
           it+1 != dots.end(); ++it)
           throw_new_points(it[0], it[1], new_dots,&mapping_straight);
        dots = new_dots;
        new_dots.clear();
        for (auto it =dots_reversed.begin();
                 it+1 != dots_reversed.end(); ++it)
           throw_new_points(it[0], it[1], new_dots,&mapping_reversed);
        dots_reversed = new_dots;
        new_dots.clear();
}

void draw_dots()
{
    glBegin(GL_LINES);
    glColor3f(0.,0.,1.);
        for (auto it =dots.begin();
                it +1!= dots.end(); ++it)
        {

            glVertex2d(it->x, it->y);
            glVertex2d((it+1)->x, (it+1)->y);
        }
    glColor3f(1.,0.,0.);
    for (auto it =dots_reversed.begin();
            it +1!= dots_reversed.end(); ++it)
    {

        glVertex2d(it->x, it->y);
        glVertex2d((it+1)->x, (it+1)->y);
    }

    glEnd();

}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    struct timeval t1, t2;

    gettimeofday(&t1, NULL);

        approximation();

    gettimeofday(&t2, NULL);

    double t = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000;
    cout<<"Iter= "<<n<<"\tNum dots="<< dots.size()<< "\t\tT="<< t<<endl;

    draw_dots();

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

int plotWindowOpen(double param_a, vector<Point> &init_dots,vector<Point>& init_dots_reversed)
{
    a = param_a;
    dots_reversed = init_dots_reversed;
    dots = init_dots;
    glutCreateWindow("Symbol");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -1,1, -1.0, 1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutMainLoop();

    return 0;
}

