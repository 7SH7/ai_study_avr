#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_btnPush_clicked(bool checked)
{
    qDebug() << "btnPush clicked" << checked;
}


void MainWindow::on_btnPush_toggled(bool checked)
{
    qDebug() << "btnPush toggled" << checked;
}


void MainWindow::on_btnCheckable_clicked(bool checked)
{
    qDebug() << "btnCheckable clicked" << checked;
}


void MainWindow::on_btnCheckable_toggled(bool checked)
{
    qDebug() << "btnCheckable toggled" << checked;
}

