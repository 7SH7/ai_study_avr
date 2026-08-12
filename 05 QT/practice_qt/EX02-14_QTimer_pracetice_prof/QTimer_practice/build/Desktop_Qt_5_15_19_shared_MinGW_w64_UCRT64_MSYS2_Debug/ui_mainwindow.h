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
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *lblRedLED;
    QLabel *lblGreenLED;
    QPushButton *btnCase1;
    QPushButton *btnCase2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(90, 120, 271, 251));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lblRedLED = new QLabel(widget);
        lblRedLED->setObjectName(QString::fromUtf8("lblRedLED"));
        lblRedLED->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        gridLayout->addWidget(lblRedLED, 0, 0, 1, 1);

        lblGreenLED = new QLabel(widget);
        lblGreenLED->setObjectName(QString::fromUtf8("lblGreenLED"));
        lblGreenLED->setStyleSheet(QString::fromUtf8("background-color: rgb(3, 255, 32);"));

        gridLayout->addWidget(lblGreenLED, 0, 1, 1, 1);

        btnCase1 = new QPushButton(widget);
        btnCase1->setObjectName(QString::fromUtf8("btnCase1"));

        gridLayout->addWidget(btnCase1, 1, 0, 1, 2);

        btnCase2 = new QPushButton(widget);
        btnCase2->setObjectName(QString::fromUtf8("btnCase2"));

        gridLayout->addWidget(btnCase2, 2, 0, 1, 2);

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
        lblRedLED->setText(QCoreApplication::translate("MainWindow", "RED", nullptr));
        lblGreenLED->setText(QCoreApplication::translate("MainWindow", "GREEN", nullptr));
        btnCase1->setText(QCoreApplication::translate("MainWindow", "Case 1", nullptr));
        btnCase2->setText(QCoreApplication::translate("MainWindow", "Case 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
