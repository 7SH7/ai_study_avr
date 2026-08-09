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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lblDigitClock;
    QHBoxLayout *horizontalLayout;
    QLabel *lblRedLED;
    QLabel *lblGreenLED;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(346, 168);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 11, 321, 115));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblDigitClock = new QLabel(widget);
        lblDigitClock->setObjectName(QString::fromUtf8("lblDigitClock"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblDigitClock->sizePolicy().hasHeightForWidth());
        lblDigitClock->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Piboto Condensed"));
        font.setPointSize(48);
        lblDigitClock->setFont(font);
        lblDigitClock->setFrameShape(QFrame::Box);
        lblDigitClock->setFrameShadow(QFrame::Raised);
        lblDigitClock->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lblDigitClock);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblRedLED = new QLabel(widget);
        lblRedLED->setObjectName(QString::fromUtf8("lblRedLED"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblRedLED->sizePolicy().hasHeightForWidth());
        lblRedLED->setSizePolicy(sizePolicy1);
        lblRedLED->setFrameShape(QFrame::Panel);
        lblRedLED->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(lblRedLED);

        lblGreenLED = new QLabel(widget);
        lblGreenLED->setObjectName(QString::fromUtf8("lblGreenLED"));
        sizePolicy1.setHeightForWidth(lblGreenLED->sizePolicy().hasHeightForWidth());
        lblGreenLED->setSizePolicy(sizePolicy1);
        lblGreenLED->setFrameShape(QFrame::Panel);
        lblGreenLED->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(lblGreenLED);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 346, 19));
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
        lblDigitClock->setText(QString());
        lblRedLED->setText(QString());
        lblGreenLED->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
