#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myThread = new MyThread(this);

    connect(myThread , &MyThread::send_command, this, &MainWindow::handle_command);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 작업이 끝나면, signal을 만들어주는 것이 일반적!
void MainWindow::handle_command(int cmd)
{
    qDebug() << "handle_command " << cmd;

    if(cmd == 1){
        static int toggle = 0;
        toggle ^= 1;
        if(toggle){
            ui->lblRedLED->setStyleSheet("background-color:red");
        } else {
            ui->lblRedLED->setStyleSheet("background-color:black");
        }
    }
}

void MainWindow::on_btnStart_clicked()
{
    qDebug() << "Start";    // 이렇게 상황 check는 그냥 습관?

    if(myThread->is_running()){
        qDebug() << "already start";
        return;
    }
    myThread->start();
}


void MainWindow::on_btnStop_clicked()
{
    qDebug() << "Stop";
    myThread->stop();
}

