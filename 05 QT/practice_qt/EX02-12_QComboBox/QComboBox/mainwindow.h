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
    void on_cboActivate_activated(int index);

    void on_cboHighlight_highlighted(int index);

    void on_cboEditableFalse_currentIndexChanged(int index);

    void on_cboEditableFalse_currentTextChanged(const QString &arg1);

    void on_cboEditableFalse_editTextChanged(const QString &arg1);

    void on_cboEditableTrue_currentIndexChanged(int index);

    void on_cboEditableTrue_currentTextChanged(const QString &arg1);

    void on_cboEditableTrue_editTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
