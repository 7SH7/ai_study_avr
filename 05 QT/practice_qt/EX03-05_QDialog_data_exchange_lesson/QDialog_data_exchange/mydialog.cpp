#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    ui->lblName->setText(name);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::receive_name(QString str)
{
    qDebug() << "receive_name" << str;
    ui->lblName->setText(str);
}

QString MyDialog::get_data(){
#pragma region 누가 눌렀나 체크{
    QString str = QString("Hobby:");
    int one_or_more = 0;
    if(ui->chkFishing->isChecked())
    {
        one_or_more++;
        str.append(" Fishing");
    }
    if(ui->chkSurfing->isChecked())
    {
        one_or_more++;
        str.append(" Surfing");
    }
    if(ui->chkTraveling->isChecked())
    {
        one_or_more++;
        str.append(" Traveling");
    }
    if(one_or_more == 0)
    {
        str.append(" None");
    }
    return str;

#pragma endregion 누가 눌렀나 체크}
}

void MyDialog::on_btnOK_clicked()
{
    accept();
}


void MyDialog::on_btnCancel_clicked()
{
    reject();
}

