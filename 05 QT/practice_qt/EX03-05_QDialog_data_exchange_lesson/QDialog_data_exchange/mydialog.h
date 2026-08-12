#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr, QString name = "");
    ~MyDialog();
    QString get_data();

private:
    Ui::MyDialog *ui;

private slots:
    void receive_name(QString);

    void on_btnOK_clicked();
    void on_btnCancel_clicked();
};

#endif // MYDIALOG_H
