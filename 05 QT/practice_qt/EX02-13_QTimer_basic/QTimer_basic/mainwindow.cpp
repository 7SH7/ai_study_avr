#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeTick()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeTick()
{
    static int toggle;
    QString str = QTime::currentTime().toString("HH:mm:ss");
    ui->lblDigitClock->setText(str);
    if(toggle++ % 2 == 0) {
        ui->lblRedLED->setStyleSheet("background-color: red");
        ui->lblGreenLED->setStyleSheet("background-color: black");
    }
    else {
        ui->lblRedLED->setStyleSheet("background-color: black");
        ui->lblGreenLED->setStyleSheet("background-color: green");
    }
}
