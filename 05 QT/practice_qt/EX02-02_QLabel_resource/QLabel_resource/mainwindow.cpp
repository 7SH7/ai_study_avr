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

// void MainWinow::on_btnPush_clicked(){
//     QPixmap p("C:\Users\kccistc\Desktop\ai_study_avr\05 QT\practice_qt\EX02-02_QLabel_resource\QLabel_resource\images\settings.png");
//     ui->label_3->setPixmap(p);
// }


void MainWindow::on_btnPush_clicked(){
    QPixmap p(":icon/images/setting.png");

    ui->label_3->setPixmap(p);
}
