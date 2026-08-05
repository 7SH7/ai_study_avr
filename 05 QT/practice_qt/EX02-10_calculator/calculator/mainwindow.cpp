#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Eval.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Eval eval;
    QString expr = "12+34";
    double res = eval.Evaluate(expr.toStdString());
    QString qstr = QString("%1").arg(res);
    expr.append("=");
    expr.append(qstr);
    qDebug() << expr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnEqual_clicked()
{

}


void MainWindow::on_btn0_clicked()
{

}


void MainWindow::on_btn1_clicked()
{

}


void MainWindow::on_btn2_clicked()
{

}


void MainWindow::on_btn3_clicked()
{

}


void MainWindow::on_btn4_clicked()
{

}


void MainWindow::on_btn5_clicked()
{

}


void MainWindow::on_btn6_clicked()
{

}


void MainWindow::on_btn7_clicked()
{

}


void MainWindow::on_btn8_clicked()
{

}


void MainWindow::on_btn9_clicked()
{

}


void MainWindow::on_btnOpen_clicked()
{

}


void MainWindow::on_btnClose_clicked()
{

}


void MainWindow::on_btnDiv_clicked()
{

}


void MainWindow::on_btnMul_clicked()
{

}


void MainWindow::on_btnPlus_clicked()
{

}


void MainWindow::on_btnMinus_clicked()
{

}


void MainWindow::on_btnPoint_clicked()
{

}


void MainWindow::on_btnBackspace_clicked()
{

}


void MainWindow::on_btnCancel_clicked()
{

}

