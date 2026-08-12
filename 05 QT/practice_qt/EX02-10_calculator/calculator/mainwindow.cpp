#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Eval.h"

// QAbstractButton의 short cut 쓰면 키보드 클릭 시, 작동 되도록 변경 가능.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonGroup,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            &MainWindow::make_String);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_String(QAbstractButton *btn)
{
    expr.append(btn->text());
    qDebug() << expr;

    ui->lblResult->setText(expr);
}

void MainWindow::on_btnEqual_clicked()
{
    Eval eval;
    expr.append('=');

    double res = eval.Evaluate(expr.toStdString());
    expr.append(QString::number(res));

    qDebug() <<  res;

    ui->lblResult->setText(expr);

    expr = "";
}

void MainWindow::on_btnBackspace_clicked()
{
    expr.chop(1);
    ui->lblResult->setText(expr);
}


void MainWindow::on_btnCancel_clicked()
{
    expr = "";
    ui->lblResult->setText("0");
}

#pragma region 사용안함 {

// void MainWindow::on_btn0_clicked()
// {

// }


// void MainWindow::on_btn1_clicked()
// {

// }


// void MainWindow::on_btn2_clicked()
// {

// }


// void MainWindow::on_btn3_clicked()
// {

// }


// void MainWindow::on_btn4_clicked()
// {

// }


// void MainWindow::on_btn5_clicked()
// {

// }


// void MainWindow::on_btn6_clicked()
// {

// }


// void MainWindow::on_btn7_clicked()
// {

// }


// void MainWindow::on_btn8_clicked()
// {

// }


// void MainWindow::on_btn9_clicked()
// {

// }


// void MainWindow::on_btnOpen_clicked()
// {

// }


// void MainWindow::on_btnClose_clicked()
// {

// }


// void MainWindow::on_btnDiv_clicked()
// {

// }


// void MainWindow::on_btnMul_clicked()
// {

// }


// void MainWindow::on_btnPlus_clicked()
// {

// }


// void MainWindow::on_btnMinus_clicked()
// {

// }


// void MainWindow::on_btnPoint_clicked()
// {

// }

#pragma endregion 사용안함 }

