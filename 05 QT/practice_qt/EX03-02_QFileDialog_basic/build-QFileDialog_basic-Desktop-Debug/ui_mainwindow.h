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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *btnGetOpenFile;
    QLabel *lblOpenFileName;
    QPushButton *btnGetSaveFile;
    QLabel *lblSaveFileName;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 127);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 361, 62));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnGetOpenFile = new QPushButton(widget);
        btnGetOpenFile->setObjectName(QString::fromUtf8("btnGetOpenFile"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnGetOpenFile->sizePolicy().hasHeightForWidth());
        btnGetOpenFile->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnGetOpenFile, 0, 0, 1, 1);

        lblOpenFileName = new QLabel(widget);
        lblOpenFileName->setObjectName(QString::fromUtf8("lblOpenFileName"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblOpenFileName->sizePolicy().hasHeightForWidth());
        lblOpenFileName->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lblOpenFileName, 0, 1, 1, 1);

        btnGetSaveFile = new QPushButton(widget);
        btnGetSaveFile->setObjectName(QString::fromUtf8("btnGetSaveFile"));
        sizePolicy.setHeightForWidth(btnGetSaveFile->sizePolicy().hasHeightForWidth());
        btnGetSaveFile->setSizePolicy(sizePolicy);

        gridLayout->addWidget(btnGetSaveFile, 1, 0, 1, 1);

        lblSaveFileName = new QLabel(widget);
        lblSaveFileName->setObjectName(QString::fromUtf8("lblSaveFileName"));
        sizePolicy1.setHeightForWidth(lblSaveFileName->sizePolicy().hasHeightForWidth());
        lblSaveFileName->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lblSaveFileName, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 19));
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
        btnGetOpenFile->setText(QCoreApplication::translate("MainWindow", "getOpenFile", nullptr));
        lblOpenFileName->setText(QCoreApplication::translate("MainWindow", "No file selected", nullptr));
        btnGetSaveFile->setText(QCoreApplication::translate("MainWindow", "getSaveFile", nullptr));
        lblSaveFileName->setText(QCoreApplication::translate("MainWindow", "No file selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
