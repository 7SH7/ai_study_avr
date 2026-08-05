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


void MainWindow::on_lineIn_editingFinished()
{
    qDebug() << "editingFinished";
}


void MainWindow::on_lineIn_returnPressed()
{
    qDebug() << "returnPressed";
}


void MainWindow::on_lineIn_textChanged(const QString &arg1)
{
    qDebug() << "textChanged";
}


void MainWindow::on_lineIn_textEdited(const QString &arg1)
{
    qDebug() << "textEdited";
}


void MainWindow::on_btnSetText_clicked()
{
    ui->lineIn->setText(ui->lineSet->text());
}


void MainWindow::on_radioPassword_clicked()
{
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}


void MainWindow::on_radioNoEcho_clicked()
{
    ui->lineEdit->setEchoMode(QLineEdit::NoEcho);
}


void MainWindow::on_btmDisplayText_clicked()
{
    ui->lblDisplayText->setText(ui->lineEdit->displayText());
}


void MainWindow::on_btnText_clicked()
{
    ui->lblText->setText(ui->lineEdit->text());
}

