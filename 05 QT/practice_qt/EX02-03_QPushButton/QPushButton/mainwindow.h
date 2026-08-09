#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
    void on_btnPush_clicked();

    void on_btnDisabled_clicked();

    void on_btnFlat_clicked();

    void on_btnCheckable_clicked();

    void on_btnAutoRepeat_clicked();

    void on_btnDefault_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
