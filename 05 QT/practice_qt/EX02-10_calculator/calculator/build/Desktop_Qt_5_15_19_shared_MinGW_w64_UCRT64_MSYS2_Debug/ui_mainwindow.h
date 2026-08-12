/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QPushButton *btnEqual;
    QPushButton *btnBackspace;
    QPushButton *btnOpen;
    QPushButton *btn5;
    QPushButton *btnCancel;
    QPushButton *btnClose;
    QPushButton *btnDiv;
    QPushButton *btn1;
    QPushButton *btnMinus;
    QPushButton *btnPoint;
    QPushButton *btn8;
    QPushButton *btnPlus;
    QPushButton *btn0;
    QPushButton *btn9;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn6;
    QPushButton *btn2;
    QPushButton *btn7;
    QPushButton *btnMul;
    QLabel *lblResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(504, 271);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnEqual = new QPushButton(centralwidget);
        btnEqual->setObjectName(QString::fromUtf8("btnEqual"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnEqual->sizePolicy().hasHeightForWidth());
        btnEqual->setSizePolicy(sizePolicy);
        btnEqual->setMinimumSize(QSize(0, 0));
        btnEqual->setMaximumSize(QSize(1000, 1000));
        btnEqual->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnEqual, 1, 4, 5, 1);

        btnBackspace = new QPushButton(centralwidget);
        btnBackspace->setObjectName(QString::fromUtf8("btnBackspace"));
        btnBackspace->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnBackspace, 1, 0, 1, 1);

        btnOpen = new QPushButton(centralwidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(btnOpen);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnOpen, 1, 2, 1, 1);

        btn5 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn5);
        btn5->setObjectName(QString::fromUtf8("btn5"));

        gridLayout->addWidget(btn5, 3, 1, 1, 1);

        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnCancel, 1, 1, 1, 1);

        btnClose = new QPushButton(centralwidget);
        buttonGroup->addButton(btnClose);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnClose, 1, 3, 1, 1);

        btnDiv = new QPushButton(centralwidget);
        buttonGroup->addButton(btnDiv);
        btnDiv->setObjectName(QString::fromUtf8("btnDiv"));
        btnDiv->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnDiv, 2, 3, 1, 1);

        btn1 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn1);
        btn1->setObjectName(QString::fromUtf8("btn1"));

        gridLayout->addWidget(btn1, 4, 0, 1, 1);

        btnMinus = new QPushButton(centralwidget);
        buttonGroup->addButton(btnMinus);
        btnMinus->setObjectName(QString::fromUtf8("btnMinus"));
        btnMinus->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnMinus, 5, 3, 1, 1);

        btnPoint = new QPushButton(centralwidget);
        buttonGroup->addButton(btnPoint);
        btnPoint->setObjectName(QString::fromUtf8("btnPoint"));

        gridLayout->addWidget(btnPoint, 5, 2, 1, 1);

        btn8 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn8);
        btn8->setObjectName(QString::fromUtf8("btn8"));

        gridLayout->addWidget(btn8, 2, 1, 1, 1);

        btnPlus = new QPushButton(centralwidget);
        buttonGroup->addButton(btnPlus);
        btnPlus->setObjectName(QString::fromUtf8("btnPlus"));
        btnPlus->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnPlus, 4, 3, 1, 1);

        btn0 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn0);
        btn0->setObjectName(QString::fromUtf8("btn0"));

        gridLayout->addWidget(btn0, 5, 0, 1, 2);

        btn9 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn9);
        btn9->setObjectName(QString::fromUtf8("btn9"));

        gridLayout->addWidget(btn9, 2, 2, 1, 1);

        btn3 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn3);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 4, 2, 1, 1);

        btn4 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn4);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 3, 0, 1, 1);

        btn6 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn6);
        btn6->setObjectName(QString::fromUtf8("btn6"));

        gridLayout->addWidget(btn6, 3, 2, 1, 1);

        btn2 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn2);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout->addWidget(btn2, 4, 1, 1, 1);

        btn7 = new QPushButton(centralwidget);
        buttonGroup->addButton(btn7);
        btn7->setObjectName(QString::fromUtf8("btn7"));

        gridLayout->addWidget(btn7, 2, 0, 1, 1);

        btnMul = new QPushButton(centralwidget);
        buttonGroup->addButton(btnMul);
        btnMul->setObjectName(QString::fromUtf8("btnMul"));
        btnMul->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btnMul, 3, 3, 1, 1);

        lblResult = new QLabel(centralwidget);
        lblResult->setObjectName(QString::fromUtf8("lblResult"));
        lblResult->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));
        lblResult->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(lblResult, 0, 4, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 504, 22));
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
        btnEqual->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnBackspace->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btnClose->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnMinus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnPoint->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        lblResult->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
