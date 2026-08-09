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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *gboxToggleStateChanged;
    QCheckBox *chkTri;
    QGroupBox *gboxICanUseIt;
    QCheckBox *chkC;
    QCheckBox *chkCpp;
    QCheckBox *chkJava;
    QCheckBox *chkPython;
    QLabel *lblMsg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gboxToggleStateChanged = new QGroupBox(centralwidget);
        gboxToggleStateChanged->setObjectName(QString::fromUtf8("gboxToggleStateChanged"));
        gboxToggleStateChanged->setGeometry(QRect(20, 20, 261, 81));
        gboxToggleStateChanged->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        chkTri = new QCheckBox(gboxToggleStateChanged);
        chkTri->setObjectName(QString::fromUtf8("chkTri"));
        chkTri->setGeometry(QRect(20, 40, 85, 20));
        chkTri->setTristate(true);
        gboxICanUseIt = new QGroupBox(centralwidget);
        gboxICanUseIt->setObjectName(QString::fromUtf8("gboxICanUseIt"));
        gboxICanUseIt->setGeometry(QRect(20, 120, 261, 121));
        gboxICanUseIt->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        chkC = new QCheckBox(gboxICanUseIt);
        chkC->setObjectName(QString::fromUtf8("chkC"));
        chkC->setGeometry(QRect(20, 60, 85, 20));
        chkCpp = new QCheckBox(gboxICanUseIt);
        chkCpp->setObjectName(QString::fromUtf8("chkCpp"));
        chkCpp->setGeometry(QRect(130, 60, 85, 20));
        chkJava = new QCheckBox(gboxICanUseIt);
        chkJava->setObjectName(QString::fromUtf8("chkJava"));
        chkJava->setGeometry(QRect(20, 90, 85, 20));
        chkPython = new QCheckBox(gboxICanUseIt);
        chkPython->setObjectName(QString::fromUtf8("chkPython"));
        chkPython->setGeometry(QRect(130, 90, 85, 20));
        lblMsg = new QLabel(gboxICanUseIt);
        lblMsg->setObjectName(QString::fromUtf8("lblMsg"));
        lblMsg->setGeometry(QRect(20, 30, 391, 16));
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
        gboxToggleStateChanged->setTitle(QCoreApplication::translate("MainWindow", "toggle/stateChanged", nullptr));
        chkTri->setText(QCoreApplication::translate("MainWindow", "3 state", nullptr));
        gboxICanUseIt->setTitle(QCoreApplication::translate("MainWindow", "I can use it", nullptr));
        chkC->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        chkCpp->setText(QCoreApplication::translate("MainWindow", "C++", nullptr));
        chkJava->setText(QCoreApplication::translate("MainWindow", "Java", nullptr));
        chkPython->setText(QCoreApplication::translate("MainWindow", "Python", nullptr));
        lblMsg->setText(QCoreApplication::translate("MainWindow", "I have no language available", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
