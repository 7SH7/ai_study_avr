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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblHello;
    QPushButton *btnHello;
    QPushButton *btnWorld;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lblHello = new QLabel(centralwidget);
        lblHello->setObjectName(QString::fromUtf8("lblHello"));
        lblHello->setGeometry(QRect(30, 10, 221, 201));
        QFont font;
        font.setFamily(QString::fromUtf8("\355\234\264\353\250\274\354\227\221\354\212\244\355\217\254"));
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        lblHello->setFont(font);
        lblHello->setStyleSheet(QString::fromUtf8("font: 9pt \"\355\234\264\353\250\274\354\227\221\354\212\244\355\217\254\";\n"
"background-color: rgb(219, 110, 255);"));
        lblHello->setTextFormat(Qt::TextFormat::AutoText);
        lblHello->setPixmap(QPixmap(QString::fromUtf8("../../images/Lighthouse.jpg")));
        lblHello->setScaledContents(true);
        lblHello->setMargin(5);
        lblHello->setIndent(13);
        lblHello->setOpenExternalLinks(true);
        btnHello = new QPushButton(centralwidget);
        btnHello->setObjectName(QString::fromUtf8("btnHello"));
        btnHello->setGeometry(QRect(190, 230, 91, 20));
        btnWorld = new QPushButton(centralwidget);
        btnWorld->setObjectName(QString::fromUtf8("btnWorld"));
        btnWorld->setGeometry(QRect(10, 230, 75, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1635, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblHello->setText(QString());
        btnHello->setText(QCoreApplication::translate("MainWindow", "Hello", nullptr));
        btnWorld->setText(QCoreApplication::translate("MainWindow", "World", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
