#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void applyBtn1();
    void applyBtn2();
    void check_btn();

private:
    Ui::MainWindow *ui;
    bool btn1_clicked = true;
    bool btn2_clicked = false;
};
#endif // MAINWINDOW_H
