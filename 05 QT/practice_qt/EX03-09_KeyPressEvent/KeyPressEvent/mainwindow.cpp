#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pos_x = 40;
    pos_y = 40;
    move_block(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
            qDebug() << "Up";
            move_block(0, -20);
            break;
        case Qt::Key_Down:
            qDebug() << "Down";
            move_block(0, 20);
            break;
        case Qt::Key_Left:
            qDebug() << "Left";
            move_block(-20, 0);
            break;
        case Qt::Key_Right:
            qDebug() << "Right";
            move_block(20, 0);
            break;
        default:
            break;
    }
}

void MainWindow::move_block(int inc_x, int inc_y)
{
    if(inc_x < 0 && pos_x == 0) return;
    if(inc_x > 0 && pos_x == 80) return;
    if(inc_y < 0 && pos_y == 0) return;
    if(inc_y > 0 && pos_y == 80) return;
    pos_x += inc_x;
    pos_y += inc_y;
    ui->lblBlock->move(pos_x, pos_y);
}
