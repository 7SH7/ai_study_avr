#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

void MainWindow::on_btnExec_clicked()
{
    // new로 할당 받는 방법
    // MyDialog *dlg = new MyDialog(this);
    // dlg-->setAttribute(Qt::WA_DeleteOnClose);
    // int r = dlg->exec();
    // qDebug() << "exec return" << r;
    // delete dlg; // 메모리정리 방법 2

    // stack에 로컬로 정의
    MyDialog dlg(this);
    int r = dlg.exec();
    if (r==QDialog::Accepted) {
        qDebug() << "Accept 됐다";
    }
    qDebug() << "exec return" << r;
}

