#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cboActivate_activated(int index)
{
    qDebug() << "activated" << index << " : " << ui->cboActivate->itemText(index);
}


void MainWindow::on_cboHighlight_highlighted(int index)
{
    qDebug() << "highlighted" << index;
}


void MainWindow::on_cboEditableFalse_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index;
}


void MainWindow::on_cboEditableFalse_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableFalse_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index << ui->cboActivate->itemText(index);
}


void MainWindow::on_cboEditableTrue_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}

void MainWindow::on_btnAct_clicked()
{

    // 하나의 아이템 추가
    ui->comboBox->addItem("풀");

    // 여러 아이템 추가 - additem
    QStringList lst = {"사과", "감자", "귤", "물"};
    lst.append("땅");
    ui->comboBox->addItems(lst);

    // 기존 아이템 선택할 때
    ui->comboBox->setCurrentText("귤");

    // 선택된 아이템의 텍스트 획득
    qDebug() << "선택된 아이템: " << ui->cboActivate->currentText();

    ui->comboBox->removeItem(1);

    int index = ui->cboHighlight->findText("item2");
    ui->cboHighlight->removeItem(index);

    // 이건 뭐지?
    ui->comboBox->insertItem(1, "밥");
}

