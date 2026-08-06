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
    QLabel *lblColor;
    QLabel *lblState;
    QPushButton *btnPush;
    QPushButton *btnCheckable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lblColor = new QLabel(centralwidget);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));
        lblColor->setGeometry(QRect(400, 190, 80, 40));
        lblColor->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        lblColor->setIndent(25);
        lblState = new QLabel(centralwidget);
        lblState->setObjectName(QString::fromUtf8("lblState"));
        lblState->setGeometry(QRect(400, 310, 80, 40));
        lblState->setStyleSheet(QString::fromUtf8("background-color: rgb(107, 255, 15);"));
        lblState->setIndent(25);
        btnPush = new QPushButton(centralwidget);
        btnPush->setObjectName(QString::fromUtf8("btnPush"));
        btnPush->setGeometry(QRect(190, 190, 81, 41));
        btnCheckable = new QPushButton(centralwidget);
        btnCheckable->setObjectName(QString::fromUtf8("btnCheckable"));
        btnCheckable->setGeometry(QRect(190, 310, 81, 41));
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
        lblColor->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        lblState->setText(QCoreApplication::translate("MainWindow", "State", nullptr));
        btnPush->setText(QCoreApplication::translate("MainWindow", "Change color", nullptr));
        btnCheckable->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
