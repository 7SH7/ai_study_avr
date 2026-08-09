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


void MainWindow::on_btnEdit_clicked()
{
    MyDialog *dlg = new MyDialog(this);
    connect(this, SIGNAL(send_name(QString)), dlg, SLOT(receive_name(QString)));
    //connect(dlg, SIGNAL(send_hobby(QString)), this, SLOT(receive_hobby(QString)));
    QString str = QString("Name: %1").arg(ui->editName->text());
    emit send_name(str);
    dlg->open();
    qDebug() << "open return";
}

void MainWindow::receive_hobby(QString str)
{
    qDebug() << "receive_hobby" << str;
    ui->lblHobby->setText(str);
}
