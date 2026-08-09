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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *lblChanged;
    QLabel *label;
    QLabel *lblSelected;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QPushButton *btnOpenMethod;
    QPushButton *btnGetColorMethod;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(344, 125);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(190, 30, 141, 44));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lblChanged = new QLabel(widget);
        lblChanged->setObjectName(QString::fromUtf8("lblChanged"));
        lblChanged->setFrameShape(QFrame::Box);
        lblChanged->setFrameShadow(QFrame::Raised);
        lblChanged->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblChanged, 0, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lblSelected = new QLabel(widget);
        lblSelected->setObjectName(QString::fromUtf8("lblSelected"));
        lblSelected->setFrameShape(QFrame::Box);
        lblSelected->setFrameShadow(QFrame::Raised);
        lblSelected->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lblSelected, 1, 1, 1, 1);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 17, 161, 71));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnOpenMethod = new QPushButton(widget1);
        btnOpenMethod->setObjectName(QString::fromUtf8("btnOpenMethod"));

        verticalLayout->addWidget(btnOpenMethod);

        btnGetColorMethod = new QPushButton(widget1);
        btnGetColorMethod->setObjectName(QString::fromUtf8("btnGetColorMethod"));

        verticalLayout->addWidget(btnGetColorMethod);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 344, 19));
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
        label_2->setText(QCoreApplication::translate("MainWindow", "changed", nullptr));
        lblChanged->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "selected", nullptr));
        lblSelected->setText(QString());
        btnOpenMethod->setText(QCoreApplication::translate("MainWindow", "open method", nullptr));
        btnGetColorMethod->setText(QCoreApplication::translate("MainWindow", "getColor method", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
