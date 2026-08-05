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


void MainWindow::on_chkTri_stateChanged(int arg1)
{
    qDebug() << "state changed" << arg1;
    qDebug() << "checkState()" << ui->chkTri->checkState();
}


void MainWindow::on_chkTri_toggled(bool checked)
{
    qDebug() << "toggled" << checked;
}

void MainWindow::process_stateChanged(void)
{
    int at_least_one = 0;
    QString msg = "I can use";
    if(ui->chkC->checkState() == Qt::Checked) {
        at_least_one++;
        msg.append(" C");
    }
    if(ui->chkCpp->checkState() == Qt::Checked) {
        at_least_one++;
        msg.append(" C++");
    }
    if(ui->chkJava->checkState() == Qt::Checked) {
        at_least_one++;
        msg.append(" Java");
    }
    if(ui->chkPython->checkState() == Qt::Checked) {
        at_least_one++;
        msg.append(" Python");
    }
    if(at_least_one == 0) {
        msg = "I have no language availble";
    }

    ui->lblMsg->setText(msg);
}

void MainWindow::on_chkC_stateChanged(int arg1)
{
    process_stateChanged();
}


void MainWindow::on_chkCpp_stateChanged(int arg1)
{
    process_stateChanged();
}


void MainWindow::on_chkJava_stateChanged(int arg1)
{
    process_stateChanged();
}


void MainWindow::on_chkPython_stateChanged(int arg1)
{
    process_stateChanged();
}

