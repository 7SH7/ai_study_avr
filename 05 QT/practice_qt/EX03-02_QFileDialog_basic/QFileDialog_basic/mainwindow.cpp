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


void MainWindow::on_btnGetOpenFile_clicked()
{
    // 디렉토리 선택

    // 1안) 풀더 딴만
    // QString dir = QFileDialog::getExistingDirectory(this, "캡션", "C:/Users/kccistc/Desktop/ai_study_avr");
    // qDebug() << dir;

    // 2안) 파일 딴만
    QString filename = QFileDialog::getOpenFileName(
        this, "Open File", "C:/Users/kccistc/Desktop/ai_study_avr", "all (*.*);; text (*.txt)");
    if(filename.isNull()) return;
    ui->lblOpenFileName->setText(filename);
}


void MainWindow::on_btnGetSaveFile_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
                this, "Save File", "/home/", "all (*.*);; text (*.txt)");
    if(filename.isNull()) return;
    ui->lblSaveFileName->setText(filename);
}

