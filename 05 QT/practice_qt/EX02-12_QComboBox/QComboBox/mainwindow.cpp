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


void MainWindow::on_cboActivate_activated(int index)
{
    qDebug() << "activated" << index;
}


void MainWindow::on_cboHighlight_highlighted(int index)
{
    qDebug() << "highlighted" << index;
}


void MainWindow::on_cboEditableFalse_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index;
}


void MainWindow::on_cboEditableFalse_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableFalse_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index;
}


void MainWindow::on_cboEditableTrue_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}
