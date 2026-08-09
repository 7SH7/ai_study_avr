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
    void on_radioFirst_toggled(bool checked);

    void on_radioSecond_toggled(bool checked);

    void on_radioThird_toggled(bool checked);

    void on_radioMale_toggled(bool checked);

    void on_radioFemale_toggled(bool checked);

    void on_btnOK_clicked();

private:
    Ui::MainWindow *ui;
    QString grade;
    QString gender;
};
#endif // MAINWINDOW_H
