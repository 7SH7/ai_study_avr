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

private slots:
    void time_tick();
    // void on_btnCase2_clicked();
    // void on_btnCase1_clicked();

private:
    Ui::MainWindow *ui;
    void led_control(bool red, bool green);
    void change_mode(int m);
    QTimer *timer;
    int tick;
    int mode;
    bool rstatus;
    bool gstatus;
};
#endif // MAINWINDOW_H
