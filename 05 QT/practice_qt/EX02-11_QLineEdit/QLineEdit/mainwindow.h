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
    void on_lineIn_editingFinished();

    void on_lineIn_returnPressed();

    void on_lineIn_textChanged(const QString &arg1);

    void on_lineIn_textEdited(const QString &arg1);

    void on_btnSetText_clicked();

    void on_radioPassword_clicked();

    void on_radioNoEcho_clicked();

    void on_btmDisplayText_clicked();

    void on_btnText_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
