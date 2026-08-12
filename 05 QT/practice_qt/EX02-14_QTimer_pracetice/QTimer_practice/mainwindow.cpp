#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);

    ui->lblRedLED->setStyleSheet("background-color: black");
    ui->lblGreenLED->setStyleSheet("background-color: green");

    connect(timer, &QTimer::timeout, this, &MainWindow::check_btn);

    connect(ui->btnCase1, &QPushButton::clicked, this, &MainWindow::applyBtn1);
    connect(ui->btnCase2, &QPushButton::clicked, this, &MainWindow::applyBtn2);

    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_btn()
{
    static int i = 0;

    if(btn1_clicked)
    {
        if(i % 2 == 0){
            ui->lblRedLED->setStyleSheet("background-color: red");
            ui->lblGreenLED->setStyleSheet("background-color: black");
        } else {
            ui->lblRedLED->setStyleSheet("background-color: black");
            ui->lblGreenLED->setStyleSheet("background-color: green");
        }
    } else if(btn2_clicked)
    {
        if(i % 2 == 0){
            ui->lblRedLED->setStyleSheet("background-color: red");
            ui->lblGreenLED->setStyleSheet("background-color: black");
        } else if(i % 3 == 0){
            ui->lblRedLED->setStyleSheet("background-color: black");
            ui->lblGreenLED->setStyleSheet("background-color: green");
        }
    }

    i++;
}

void MainWindow::applyBtn1()
{
    btn1_clicked = true;
    btn2_clicked = false;

    ui->lblRedLED->setStyleSheet("background-color: black");
    ui->lblGreenLED->setStyleSheet("background-color: black");
}

void MainWindow::applyBtn2()
{
    btn1_clicked = false;
    btn2_clicked = true;

    ui->lblRedLED->setStyleSheet("background-color: black");
    ui->lblGreenLED->setStyleSheet("background-color: black");
}
