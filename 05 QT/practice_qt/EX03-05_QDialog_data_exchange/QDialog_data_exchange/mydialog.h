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
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private:
    Ui::MyDialog *ui;

signals:
    void send_hobby(QString);

private slots:
    void receive_name(QString);

    void on_btnOK_clicked();
    void on_btnCancel_clicked();
};

#endif // MYDIALOG_H
