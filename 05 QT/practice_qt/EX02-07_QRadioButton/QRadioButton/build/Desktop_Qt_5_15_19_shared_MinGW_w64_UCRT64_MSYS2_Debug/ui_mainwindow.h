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
#include <QtWidgets/QCheckBox>
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
    QGroupBox *groupBox;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 1125);
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
        lblMsg->setFrameShape(QFrame::Shape::NoFrame);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 310, 120, 201));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(20, 110, 89, 20));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 80, 89, 20));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(20, 50, 89, 20));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(190, 310, 120, 201));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 90, 89, 20));
        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(10, 60, 89, 20));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(50, 560, 76, 20));
        checkBox->setAutoExclusive(false);
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(50, 600, 76, 20));
        checkBox_3 = new QCheckBox(centralwidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(50, 640, 76, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 580, 75, 24));
        pushButton->setCheckable(true);
        pushButton->setAutoExclusive(true);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 580, 75, 24));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoExclusive(true);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(330, 580, 75, 24));
        pushButton_3->setCheckable(true);
        pushButton_3->setAutoExclusive(true);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(170, 640, 281, 80));
        pushButton_6 = new QPushButton(groupBox_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(180, 20, 75, 24));
        pushButton_6->setCheckable(true);
        pushButton_6->setAutoExclusive(true);
        pushButton_5 = new QPushButton(groupBox_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(40, 20, 75, 24));
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);
        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(110, 20, 75, 24));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "3\355\225\231\353\205\204", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "2\355\225\231\353\205\204", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "1\355\225\231\353\205\204", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "\354\227\254\354\236\220", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "\353\202\250\354\236\220", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2341", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2342", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2343", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2343", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2341", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\353\252\250\353\223\2342", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
