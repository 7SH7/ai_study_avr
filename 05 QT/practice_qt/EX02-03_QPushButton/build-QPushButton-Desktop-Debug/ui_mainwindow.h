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
    QPushButton *btnPush;
    QPushButton *btnDisabled;
    QPushButton *btnFlat;
    QPushButton *btnCheckable;
    QPushButton *btnAutoRepeat;
    QPushButton *btnDefault;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnPush = new QPushButton(centralwidget);
        btnPush->setObjectName(QString::fromUtf8("btnPush"));
        btnPush->setGeometry(QRect(20, 20, 101, 41));
        btnDisabled = new QPushButton(centralwidget);
        btnDisabled->setObjectName(QString::fromUtf8("btnDisabled"));
        btnDisabled->setEnabled(false);
        btnDisabled->setGeometry(QRect(170, 20, 91, 41));
        btnFlat = new QPushButton(centralwidget);
        btnFlat->setObjectName(QString::fromUtf8("btnFlat"));
        btnFlat->setGeometry(QRect(300, 20, 91, 41));
        btnFlat->setFlat(true);
        btnCheckable = new QPushButton(centralwidget);
        btnCheckable->setObjectName(QString::fromUtf8("btnCheckable"));
        btnCheckable->setGeometry(QRect(20, 70, 101, 41));
        btnCheckable->setCheckable(true);
        btnAutoRepeat = new QPushButton(centralwidget);
        btnAutoRepeat->setObjectName(QString::fromUtf8("btnAutoRepeat"));
        btnAutoRepeat->setGeometry(QRect(170, 70, 91, 41));
        btnAutoRepeat->setAutoRepeat(true);
        btnDefault = new QPushButton(centralwidget);
        btnDefault->setObjectName(QString::fromUtf8("btnDefault"));
        btnDefault->setGeometry(QRect(300, 70, 101, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        btnDefault->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnPush->setText(QCoreApplication::translate("MainWindow", "push button", nullptr));
        btnDisabled->setText(QCoreApplication::translate("MainWindow", "disabled", nullptr));
        btnFlat->setText(QCoreApplication::translate("MainWindow", "flat", nullptr));
        btnCheckable->setText(QCoreApplication::translate("MainWindow", "checkable", nullptr));
        btnAutoRepeat->setText(QCoreApplication::translate("MainWindow", "auto repeat", nullptr));
        btnDefault->setText(QCoreApplication::translate("MainWindow", "default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
