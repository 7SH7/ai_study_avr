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

#if 0 // 강사님 코드

void MainWindow::on_btnPush_clicked()
{
    static int cnt = 0;
    static QStringList color = {"green", "blue", "red"};
    // arg(값, 전체자릿수, 진법, 채울문자)
    // QString s2 = QString("HEX: 0x%1").arg(10, 2, 16, QChar('0'));    // 예제
    QString s = QString("background-color: %1").arg(color[cnt%3]);
    ui->lblColor->setStyleSheet(s);
    cnt++;
}


#endif