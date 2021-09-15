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
    close(); /*close GUI*/
    double param_a, param_b;
    param_a = ui->aParamEdit->toPlainText().toDouble();
    param_b = ui->bParamEdit->toPlainText().toDouble();
    plotWindowOpen(param_a, param_b);

}


