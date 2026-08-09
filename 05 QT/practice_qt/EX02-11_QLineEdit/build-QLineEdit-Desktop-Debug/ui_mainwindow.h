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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLineEdit *lineIn;
    QLineEdit *lineSet;
    QPushButton *btnSetText;
    QGroupBox *groupBox_2;
    QRadioButton *radioPassword;
    QRadioButton *radioNoEcho;
    QLineEdit *lineEdit;
    QPushButton *btmDisplayText;
    QPushButton *btnText;
    QLabel *lblDisplayText;
    QLabel *lblText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 91));
        lineIn = new QLineEdit(groupBox);
        lineIn->setObjectName(QString::fromUtf8("lineIn"));
        lineIn->setGeometry(QRect(10, 30, 291, 22));
        lineSet = new QLineEdit(groupBox);
        lineSet->setObjectName(QString::fromUtf8("lineSet"));
        lineSet->setGeometry(QRect(10, 60, 181, 22));
        btnSetText = new QPushButton(groupBox);
        btnSetText->setObjectName(QString::fromUtf8("btnSetText"));
        btnSetText->setGeometry(QRect(220, 60, 80, 22));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 321, 151));
        radioPassword = new QRadioButton(groupBox_2);
        radioPassword->setObjectName(QString::fromUtf8("radioPassword"));
        radioPassword->setGeometry(QRect(30, 30, 99, 20));
        radioNoEcho = new QRadioButton(groupBox_2);
        radioNoEcho->setObjectName(QString::fromUtf8("radioNoEcho"));
        radioNoEcho->setGeometry(QRect(180, 30, 99, 20));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 60, 261, 22));
        btmDisplayText = new QPushButton(groupBox_2);
        btmDisplayText->setObjectName(QString::fromUtf8("btmDisplayText"));
        btmDisplayText->setGeometry(QRect(210, 90, 80, 22));
        btnText = new QPushButton(groupBox_2);
        btnText->setObjectName(QString::fromUtf8("btnText"));
        btnText->setGeometry(QRect(210, 120, 80, 22));
        lblDisplayText = new QLabel(groupBox_2);
        lblDisplayText->setObjectName(QString::fromUtf8("lblDisplayText"));
        lblDisplayText->setGeometry(QRect(30, 90, 151, 16));
        lblText = new QLabel(groupBox_2);
        lblText->setObjectName(QString::fromUtf8("lblText"));
        lblText->setGeometry(QRect(30, 120, 151, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "signal", nullptr));
        btnSetText->setText(QCoreApplication::translate("MainWindow", "setText", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "echo mode", nullptr));
        radioPassword->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        radioNoEcho->setText(QCoreApplication::translate("MainWindow", "NoEcho", nullptr));
        btmDisplayText->setText(QCoreApplication::translate("MainWindow", "displayText", nullptr));
        btnText->setText(QCoreApplication::translate("MainWindow", "text", nullptr));
        lblDisplayText->setText(QCoreApplication::translate("MainWindow", "using displayText", nullptr));
        lblText->setText(QCoreApplication::translate("MainWindow", "using text", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
