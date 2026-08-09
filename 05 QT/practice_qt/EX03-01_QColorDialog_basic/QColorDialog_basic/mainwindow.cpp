#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dlgColor = new QColorDialog(this);
    QObject::connect(dlgColor, SIGNAL(colorSelected(QColor)), this, SLOT(selectColor(QColor)));
    QObject::connect(dlgColor, SIGNAL(currentColorChanged(QColor)), this, SLOT(changeColor(QColor)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectColor(QColor color)
{
    qDebug() << "selectColor" << color.name();
    QString str = QString("background-color: %1").arg(color.name());
    ui->lblSelected->setStyleSheet(str);
}

void MainWindow::changeColor(QColor color)
{
    qDebug() << "changeColor" << color.name();
    QString str = QString("background-color: %1").arg(color.name());
    ui->lblChanged->setStyleSheet(str);
}

void MainWindow::on_btnOpenMethod_clicked()
{
    dlgColor->setOption(QColorDialog::ShowAlphaChannel);
    dlgColor->open();
}


void MainWindow::on_btnGetColorMethod_clicked()
{
    qDebug() << "on_btnGetColorMethod_clicked";
    QColorDialog::ColorDialogOptions opts = QColorDialog::ShowAlphaChannel;
    QColor color = QColorDialog::getColor(Qt::red, this, "Select Color", opts);
    if(color.isValid())
    {
        qDebug() << "isValid" << color.name();
        QString str = QString("background-color: %1").arg(color.name());
        ui->lblSelected->setStyleSheet(str);
    }
}

