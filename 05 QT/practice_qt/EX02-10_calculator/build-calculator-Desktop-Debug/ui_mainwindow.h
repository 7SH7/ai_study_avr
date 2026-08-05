/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblResult;
    QPushButton *btnEqual;
    QPushButton *btnMinus;
    QPushButton *btnPoint;
    QPushButton *btn0;
    QPushButton *btnPlus;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn1;
    QPushButton *btnMul;
    QPushButton *btn5;
    QPushButton *btn4;
    QPushButton *btn6;
    QPushButton *btn9;
    QPushButton *btnDiv;
    QPushButton *btn8;
    QPushButton *btn7;
    QPushButton *btnBackspace;
    QPushButton *btnOpen;
    QPushButton *btnClose;
    QPushButton *btnCancel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(504, 271);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lblResult = new QLabel(centralwidget);
        lblResult->setObjectName(QString::fromUtf8("lblResult"));
        lblResult->setGeometry(QRect(9, 9, 16, 19));
        lblResult->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));
        lblResult->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnEqual = new QPushButton(centralwidget);
        btnEqual->setObjectName(QString::fromUtf8("btnEqual"));
        btnEqual->setGeometry(QRect(358, 57, 80, 22));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnEqual->sizePolicy().hasHeightForWidth());
        btnEqual->setSizePolicy(sizePolicy);
        btnEqual->setMinimumSize(QSize(0, 0));
        btnEqual->setMaximumSize(QSize(1000, 1000));
        btnEqual->setStyleSheet(QString::fromUtf8(""));
        btnMinus = new QPushButton(centralwidget);
        btnMinus->setObjectName(QString::fromUtf8("btnMinus"));
        btnMinus->setGeometry(QRect(184, 179, 80, 22));
        btnMinus->setStyleSheet(QString::fromUtf8(""));
        btnPoint = new QPushButton(centralwidget);
        btnPoint->setObjectName(QString::fromUtf8("btnPoint"));
        btnPoint->setGeometry(QRect(98, 179, 80, 22));
        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setGeometry(QRect(12, 179, 80, 22));
        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName(QString::fromUtf8("btnPlus"));
        btnPlus->setGeometry(QRect(270, 149, 80, 22));
        btnPlus->setStyleSheet(QString::fromUtf8(""));
        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(98, 149, 80, 22));
        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(184, 149, 80, 22));
        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(12, 149, 80, 22));
        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName(QString::fromUtf8("btnMul"));
        btnMul->setGeometry(QRect(270, 119, 80, 22));
        btnMul->setStyleSheet(QString::fromUtf8(""));
        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setGeometry(QRect(98, 119, 80, 22));
        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(12, 119, 80, 22));
        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setGeometry(QRect(184, 119, 80, 22));
        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        btn9->setGeometry(QRect(184, 89, 80, 22));
        btnDiv = new QPushButton(centralwidget);
        btnDiv->setObjectName(QString::fromUtf8("btnDiv"));
        btnDiv->setGeometry(QRect(270, 89, 80, 22));
        btnDiv->setStyleSheet(QString::fromUtf8(""));
        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        btn8->setGeometry(QRect(98, 89, 80, 22));
        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setGeometry(QRect(12, 89, 80, 22));
        btnBackspace = new QPushButton(centralwidget);
        btnBackspace->setObjectName(QString::fromUtf8("btnBackspace"));
        btnBackspace->setGeometry(QRect(12, 59, 80, 22));
        btnBackspace->setStyleSheet(QString::fromUtf8(""));
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(184, 59, 80, 22));
        btnOpen->setStyleSheet(QString::fromUtf8(""));
        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(270, 59, 80, 22));
        btnClose->setStyleSheet(QString::fromUtf8(""));
        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(98, 59, 80, 22));
        btnCancel->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 504, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblResult->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnEqual->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnMinus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnPoint->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnBackspace->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
