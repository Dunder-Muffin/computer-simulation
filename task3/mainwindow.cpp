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
    double param_a, param_b;
    param_a = ui->aParamEdit->toPlainText().toDouble();
    param_b = ui->bParamEdit->toPlainText().toDouble();


    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->appendPlainText(QString::fromStdString(topologicalSort(param_a, param_b)));
}


void MainWindow::on_pushButton_2_clicked()
{
   ui->plainTextEdit->clear();
}

