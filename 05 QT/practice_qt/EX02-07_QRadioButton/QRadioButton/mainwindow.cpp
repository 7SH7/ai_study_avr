#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grade = "First";
    gender = "Male";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioFirst_toggled(bool checked)
{
    if(checked == true) {
        grade = "First";
    }
}


void MainWindow::on_radioSecond_toggled(bool checked)
{
    if(checked == true) {
        grade = "Second";
    }
}


void MainWindow::on_radioThird_toggled(bool checked)
{
    if(checked == true) {
        grade = "Third";
    }
}


void MainWindow::on_radioMale_toggled(bool checked)
{
    if(checked == true) {
        gender = "Male";
    }
}


void MainWindow::on_radioFemale_toggled(bool checked)
{
    if(checked == true) {
        gender = "Female";
    }
}


void MainWindow::on_btnOK_clicked()
{
    QString msg = QString("%1 grade / %2").arg(grade).arg(gender);
    ui->lblMsg->setText(msg);
}

