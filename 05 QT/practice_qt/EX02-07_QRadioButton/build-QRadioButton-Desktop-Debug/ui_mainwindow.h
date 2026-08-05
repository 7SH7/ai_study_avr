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
    QGroupBox *gboxGrade;
    QRadioButton *radioThird;
    QRadioButton *radioSecond;
    QRadioButton *radioFirst;
    QGroupBox *gboxGender;
    QRadioButton *radioMale;
    QRadioButton *radioFemale;
    QPushButton *btnOK;
    QLabel *lblMsg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gboxGrade = new QGroupBox(centralwidget);
        gboxGrade->setObjectName(QString::fromUtf8("gboxGrade"));
        gboxGrade->setGeometry(QRect(10, 10, 440, 80));
        gboxGrade->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        radioThird = new QRadioButton(gboxGrade);
        radioThird->setObjectName(QString::fromUtf8("radioThird"));
        radioThird->setGeometry(QRect(350, 30, 99, 20));
        radioSecond = new QRadioButton(gboxGrade);
        radioSecond->setObjectName(QString::fromUtf8("radioSecond"));
        radioSecond->setGeometry(QRect(190, 30, 99, 20));
        radioFirst = new QRadioButton(gboxGrade);
        radioFirst->setObjectName(QString::fromUtf8("radioFirst"));
        radioFirst->setGeometry(QRect(50, 30, 99, 20));
        radioFirst->setChecked(true);
        gboxGender = new QGroupBox(centralwidget);
        gboxGender->setObjectName(QString::fromUtf8("gboxGender"));
        gboxGender->setGeometry(QRect(10, 110, 440, 80));
        gboxGender->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        radioMale = new QRadioButton(gboxGender);
        radioMale->setObjectName(QString::fromUtf8("radioMale"));
        radioMale->setGeometry(QRect(50, 30, 99, 20));
        radioMale->setChecked(true);
        radioMale->setAutoExclusive(true);
        radioFemale = new QRadioButton(gboxGender);
        radioFemale->setObjectName(QString::fromUtf8("radioFemale"));
        radioFemale->setGeometry(QRect(190, 30, 99, 20));
        btnOK = new QPushButton(centralwidget);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(10, 220, 91, 41));
        lblMsg = new QLabel(centralwidget);
        lblMsg->setObjectName(QString::fromUtf8("lblMsg"));
        lblMsg->setGeometry(QRect(150, 220, 301, 31));
        lblMsg->setStyleSheet(QString::fromUtf8(""));
        lblMsg->setFrameShape(QFrame::NoFrame);
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
        gboxGrade->setTitle(QCoreApplication::translate("MainWindow", "Grade", nullptr));
        radioThird->setText(QCoreApplication::translate("MainWindow", "Third", nullptr));
        radioSecond->setText(QCoreApplication::translate("MainWindow", "Second", nullptr));
        radioFirst->setText(QCoreApplication::translate("MainWindow", "First", nullptr));
        gboxGender->setTitle(QCoreApplication::translate("MainWindow", "Gender", nullptr));
        radioMale->setText(QCoreApplication::translate("MainWindow", "Male", nullptr));
        radioFemale->setText(QCoreApplication::translate("MainWindow", "Female", nullptr));
        btnOK->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        lblMsg->setText(QCoreApplication::translate("MainWindow", "First grade / Male", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
