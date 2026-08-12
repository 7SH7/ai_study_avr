#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dlgColor = new QColorDialog(this);
    QObject::connect(dlgColor, SIGNAL(colorSelected(QColor)), this, SLOT(selectColor(QColor)));
    QObject::connect(dlgColor, SIGNAL(currentColorChanged(QColor)), this, SLOT(changeColor(QColor)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectColor(QColor color)
{
    qDebug() << "selectColor" << color.name();
    QString str = QString("background-color: %1").arg(color.name());
    ui->lblSelected->setStyleSheet(str);
}

void MainWindow::changeColor(QColor color)
{
    qDebug() << "changeColor" << color.name();
    QString str = QString("background-color: %1").arg(color.name());
    ui->lblChanged->setStyleSheet(str);
}

void MainWindow::on_btnOpenMethod_clicked()
{
    dlgColor->setOption(QColorDialog::ShowAlphaChannel);
    dlgColor->open();
}


void MainWindow::on_btnGetColorMethod_clicked()
{
    qDebug() << "on_btnGetColorMethod_clicked";
    QColorDialog::ColorDialogOptions opts = QColorDialog::ShowAlphaChannel; // 투명도 설정
    // 기본 선택색: 빨간색(Qt::red), 부모: this, 창 제목: "Select Color", 옵션: opts
    // 사용자가 [OK] 또는 [Cancel]을 누를 때까지 프로그램은 이 줄에서 대기합니다.
    QColor color = QColorDialog::getColor(Qt::red, this, "Select Color", opts);

    // 사용자가 [Cancel]을 누르지 않고, [OK]를 눌러 유효한 색상을 가져왔는지 확인합니다.
    if(color.isValid())
    {
        qDebug() << "isValid" << color.name();
        QString str = QString("background-color: %1").arg(color.name());
        ui->lblSelected->setStyleSheet(str);
    }
}