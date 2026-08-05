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
    QLabel *lblRichText;
    QLabel *lblPlainText;
    QLabel *lblBox;
    QLabel *lblWordWrap;
    QLabel *lblUrl;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lblRichText = new QLabel(centralwidget);
        lblRichText->setObjectName(QString::fromUtf8("lblRichText"));
        lblRichText->setGeometry(QRect(20, 20, 251, 31));
        lblRichText->setTextFormat(Qt::RichText);
        lblPlainText = new QLabel(centralwidget);
        lblPlainText->setObjectName(QString::fromUtf8("lblPlainText"));
        lblPlainText->setGeometry(QRect(20, 70, 251, 31));
        lblPlainText->setTextFormat(Qt::PlainText);
        lblBox = new QLabel(centralwidget);
        lblBox->setObjectName(QString::fromUtf8("lblBox"));
        lblBox->setGeometry(QRect(20, 120, 131, 21));
        lblBox->setStyleSheet(QString::fromUtf8("font: 16pt \"Serif\";"));
        lblBox->setFrameShape(QFrame::Box);
        lblBox->setFrameShadow(QFrame::Raised);
        lblWordWrap = new QLabel(centralwidget);
        lblWordWrap->setObjectName(QString::fromUtf8("lblWordWrap"));
        lblWordWrap->setGeometry(QRect(20, 170, 51, 41));
        lblWordWrap->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 127);"));
        lblWordWrap->setWordWrap(true);
        lblWordWrap->setIndent(10);
        lblUrl = new QLabel(centralwidget);
        lblUrl->setObjectName(QString::fromUtf8("lblUrl"));
        lblUrl->setGeometry(QRect(20, 240, 141, 31));
        lblUrl->setOpenExternalLinks(true);
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
        lblRichText->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; font-style:italic; text-decoration: underline;\">textFormat: Rich Text</span></p></body></html>", nullptr));
        lblPlainText->setText(QCoreApplication::translate("MainWindow", "textFormat: Plain Text", nullptr));
        lblBox->setText(QCoreApplication::translate("MainWindow", "Serif", nullptr));
        lblWordWrap->setText(QCoreApplication::translate("MainWindow", "Word Wrap", nullptr));
        lblUrl->setText(QCoreApplication::translate("MainWindow", "<a href=\"https://doc.qt.io\">Qt Documentation</a>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
