#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->btnPush, &QPushButton::clicked, this, this->MainWindow::ChangeColor);
    connect(ui->btnCheckable, &QPushButton::clicked, this, this->MainWindow::ChangeState);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ChangeColor()
{
    static int i = -1;
    QStringList arr = {"green", "blue", "red"};

    i = (i + 1) % 3;
    ui->lblColor->setStyleSheet("background-color:"+arr[i]);
}

void MainWindow::ChangeState()
{
    static bool isState = false;    // F(녹색) <-> T(적색)
    QStringList arr = {"green", "red"};
    QStringList name = {"OFF", "ON"};

    isState = !isState;
    ui->lblState->setStyleSheet("background-color:"+arr[isState]);
    ui->lblState->setText(name[isState]);

}