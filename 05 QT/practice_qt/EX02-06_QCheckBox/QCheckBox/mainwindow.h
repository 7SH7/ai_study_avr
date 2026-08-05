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
    void process_stateChanged(void);

private slots:
    void on_chkTri_stateChanged(int arg1);

    void on_chkTri_toggled(bool checked);

    void on_chkC_stateChanged(int arg1);

    void on_chkCpp_stateChanged(int arg1);

    void on_chkJava_stateChanged(int arg1);

    void on_chkPython_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
