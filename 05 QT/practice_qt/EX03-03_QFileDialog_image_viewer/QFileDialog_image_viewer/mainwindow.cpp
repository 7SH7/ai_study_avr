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


void MainWindow::on_btnOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this, "Open File", "C:/Users/kccistc/Desktop/ai_study_avr/05 QT/practice_qt/images", "JPEG (*.jpg; *.jpeg);; PNG(*.png)");
    if(filename.isNull()) return;
    qDebug() << filename;
    ui->lblImage->setPixmap(filename);

}

