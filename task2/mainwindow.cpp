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
    double param_a;
    param_a = ui->aParamEdit->toPlainText().toDouble();

    std::vector<Point> init_dots{
        {
            ui->x1ParamEdit->toPlainText().toDouble(),
            ui->y1ParamEdit->toPlainText().toDouble()
        },
        {
            ui->x2ParamEdit->toPlainText().toDouble(),
            ui->y2ParamEdit->toPlainText().toDouble()
        }};
    std::vector<Point> init_dots_reversed{
        {
            ui->x1ParamEdit_2->toPlainText().toDouble(),
            ui->y1ParamEdit_2->toPlainText().toDouble()
        },
        {
            ui->x2ParamEdit_2->toPlainText().toDouble(),
            ui->y2ParamEdit_2->toPlainText().toDouble()
        }};



    plotWindowOpen(param_a, init_dots, init_dots_reversed);

}

