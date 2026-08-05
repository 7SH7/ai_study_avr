#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectColor(QColor color);
    void changeColor(QColor color);
    void on_btnOpenMethod_clicked();

    void on_btnGetColorMethod_clicked();

private:
    Ui::MainWindow *ui;
    QColorDialog *dlgColor;
};
#endif // MAINWINDOW_H
