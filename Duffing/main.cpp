#include "mainwindow.h"
#include "mainPlot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    plotWindowInit(argc, argv);

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
