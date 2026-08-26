#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(ui->actionhere, &QAction::toggled, this, MainWinow::~~)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::critical(this, "title", "content");
}



void MainWindow::on_pushButton_2_clicked()
{
    int r = QMessageBox::question(this, "question", "delete?", QMessageBox::Yes|QMessageBox::No);
    if(r==QMessageBox::Yes){
        qDebug() << "Yes";
    } else {
        qDebug() << "No";
    }
}


void MainWindow::on_actionhere_triggered()
{
    qDebug() << "click new menu";
}

