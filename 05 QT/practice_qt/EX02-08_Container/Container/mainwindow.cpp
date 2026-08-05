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


void MainWindow::on_tbRadioFirst_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tool Box > Grade > First");
    }
}


void MainWindow::on_tbRedioSecond_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tool Box > Grade > Second");
    }
}


void MainWindow::on_tbRadioThird_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tool Box > Grade > Third");
    }
}


void MainWindow::on_tbRadioMale_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tool Box > Gender > Male");
    }
}


void MainWindow::on_tbRadioFemale_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tool Box > Gender > Female");
    }
}


void MainWindow::on_twRadioFirst_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tab Widget > Grade > First");
    }
}


void MainWindow::on_twRadioSecond_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tab Widget > Grade > Second");
    }
}


void MainWindow::on_twRadioThird_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tab Widget > Grade > Third");
    }
}


void MainWindow::on_twRadioMale_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tab Widget > Gender > Male");
    }
}


void MainWindow::on_twRadioFemale_toggled(bool checked)
{
    if(checked == true) {
        ui->lblMsg->setText("Tab Widget > Gender > Female");
    }
}

