#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainPlot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    double param_alpha = ui->alphaParamEdit->toPlainText().toDouble(),
            param_beta = ui->betaParamEdit->toPlainText().toDouble(),
            param_gamma = ui->gammaParamEdit->toPlainText().toDouble();
    Point starting_point =
    {
        ui->x0ParamEdit->toPlainText().toDouble(),
        ui->y0ParamEdit->toPlainText().toDouble()
    };
    double dt = ui->dtParamEdit->toPlainText().toDouble();
    double t0 = ui->t0ParamEdit->toPlainText().toDouble();

    close();    /*close GUI*/
    plotWindowOpen(param_alpha, param_beta, param_gamma, starting_point, t0, dt);

}

