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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_15;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(115, 20, 48, 16));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(169, 20, 48, 16));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 255);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(223, 20, 48, 16));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(15, 20, 48, 16));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(12, 137, 48, 16));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(12, 52, 48, 16));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(12, 114, 48, 16));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 255);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(12, 92, 48, 16));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(287, 71, 48, 16));
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 255);"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(205, 71, 48, 16));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(151, 71, 48, 16));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(205, 108, 48, 16));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 190, 48, 16));
        label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(78, 190, 48, 16));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 298, 48, 16));
        label_16->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 250, 48, 16));
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
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
        label_3->setText(QCoreApplication::translate("MainWindow", "Label12", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Label13", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Label14", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Label11", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Label24", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Label21", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Label23", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Label22", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Label33", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Label32", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Label31", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Label34", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Label41", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Label42", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Label52", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Label51", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
