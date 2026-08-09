#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_tbRadioFirst_toggled(bool checked);

    void on_tbRedioSecond_toggled(bool checked);

    void on_tbRadioThird_toggled(bool checked);

    void on_tbRadioMale_toggled(bool checked);

    void on_tbRadioFemale_toggled(bool checked);

    void on_twRadioFirst_toggled(bool checked);

    void on_twRadioSecond_toggled(bool checked);

    void on_twRadioThird_toggled(bool checked);

    void on_twRadioMale_toggled(bool checked);

    void on_twRadioFemale_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
