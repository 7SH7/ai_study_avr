#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tick = 0;
    mode = 1;
    rstatus = false;
    gstatus = false;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::time_tick);
    // connect(ui->btnCase1, &QPushButton::clicked, this, &MainWindow::change_mode(1));
    // 위처럼 하면, change_mode(1)의 return값으로 대체됨. (Err) >> 어떻게 해야하나? 이럴 때 람다식을 사용한다.
    connect(ui->btnCase1
        , &QPushButton::clicked
        , this
        ,[=](){
            change_mode(1);
        }
    );

    connect(ui->btnCase2
        , &QPushButton::clicked
        , this
        ,[=](){
            change_mode(2);
        }
    );
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_tick()
{
    tick++;

    if(tick % mode == 0){
        rstatus = !rstatus;
    }
    if(tick % (mode+1) == 0){
        gstatus = !gstatus;
    }

    led_control(rstatus, gstatus);
}

void MainWindow::led_control(bool red, bool green){
    if(red == true) ui->lblRedLED->setStyleSheet("background-color: red");
    else ui->lblRedLED->setStyleSheet("background-color: black");

    if(green == true) ui->lblGreenLED->setStyleSheet("background-color: green");
    else ui->lblGreenLED->setStyleSheet("background-color: black");
}

// signal이 생성해준 인자를 slot이 받아서 쓰니까.. > 이 int m 은 시그널로 처리
void MainWindow::change_mode(int m){

}


// void MainWindow::on_btnCase1_clicked()
// {
//     mode = 1;
//     tick = 0;
//     rstatus = false;
//     gstatus = false;
//     led_control(rstatus, gstatus);
//     timer->start(500);
// }

// void MainWindow::on_btnCase2_clicked()
// {
//     mode = 2;
//     tick = 0;
//     rstatus = false;
//     gstatus = false;
//     led_control(rstatus, gstatus);
//     timer->start(500);
// }
