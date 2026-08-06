#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 방법 1 >> 방법2 구현한 다음 추가했으니, 이게 나중에 실행됨.
    connect(ui->btnHello, &QPushButton::clicked, this, [this](){ this->ui->lblHello->setText("Hello2"); });
    connect(ui->btnWorld, &QPushButton::clicked, this, [this](){ this->ui->lblHello->setText("World2"); });

    // connect(ui->btnHello, &QPushButton::clicked, this, &MainWindow::Print_Hello);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 방법2 >> 이거 부터 등록했으니, 이거부터 실행
void MainWindow::on_btnHello_clicked()
{
    ui->lblHello->setText("Hello");
}


void MainWindow::on_btnWorld_clicked()
{
   ui->lblHello->setText("World");
}