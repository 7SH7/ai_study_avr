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
#include <QtWidgets/QLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QToolBox *tbGradeGender;
    QWidget *page_1;
    QRadioButton *tbRadioFirst;
    QRadioButton *tbRedioSecond;
    QRadioButton *tbRadioThird;
    QWidget *page_2;
    QRadioButton *tbRadioMale;
    QRadioButton *tbRadioFemale;
    QTabWidget *tabWidget;
    QWidget *tab;
    QRadioButton *twRadioFirst;
    QRadioButton *twRadioSecond;
    QRadioButton *twRadioThird;
    QWidget *tab_2;
    QRadioButton *twRadioMale;
    QRadioButton *twRadioFemale;
    QLabel *lblMsg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tbGradeGender = new QToolBox(centralwidget);
        tbGradeGender->setObjectName(QString::fromUtf8("tbGradeGender"));
        tbGradeGender->setGeometry(QRect(10, 10, 131, 141));
        tbGradeGender->setFrameShape(QFrame::NoFrame);
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        page_1->setGeometry(QRect(0, 0, 131, 85));
        tbRadioFirst = new QRadioButton(page_1);
        tbRadioFirst->setObjectName(QString::fromUtf8("tbRadioFirst"));
        tbRadioFirst->setGeometry(QRect(10, 0, 99, 20));
        tbRedioSecond = new QRadioButton(page_1);
        tbRedioSecond->setObjectName(QString::fromUtf8("tbRedioSecond"));
        tbRedioSecond->setGeometry(QRect(10, 20, 99, 20));
        tbRadioThird = new QRadioButton(page_1);
        tbRadioThird->setObjectName(QString::fromUtf8("tbRadioThird"));
        tbRadioThird->setGeometry(QRect(10, 40, 99, 20));
        tbGradeGender->addItem(page_1, QString::fromUtf8("Grade"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 131, 85));
        tbRadioMale = new QRadioButton(page_2);
        tbRadioMale->setObjectName(QString::fromUtf8("tbRadioMale"));
        tbRadioMale->setGeometry(QRect(10, 10, 99, 20));
        tbRadioFemale = new QRadioButton(page_2);
        tbRadioFemale->setObjectName(QString::fromUtf8("tbRadioFemale"));
        tbRadioFemale->setGeometry(QRect(10, 40, 99, 20));
        tbGradeGender->addItem(page_2, QString::fromUtf8("Gender"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(170, 10, 191, 121));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        twRadioFirst = new QRadioButton(tab);
        twRadioFirst->setObjectName(QString::fromUtf8("twRadioFirst"));
        twRadioFirst->setGeometry(QRect(10, 10, 99, 20));
        twRadioSecond = new QRadioButton(tab);
        twRadioSecond->setObjectName(QString::fromUtf8("twRadioSecond"));
        twRadioSecond->setGeometry(QRect(10, 35, 99, 20));
        twRadioThird = new QRadioButton(tab);
        twRadioThird->setObjectName(QString::fromUtf8("twRadioThird"));
        twRadioThird->setGeometry(QRect(10, 60, 99, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        twRadioMale = new QRadioButton(tab_2);
        twRadioMale->setObjectName(QString::fromUtf8("twRadioMale"));
        twRadioMale->setGeometry(QRect(10, 10, 99, 20));
        twRadioFemale = new QRadioButton(tab_2);
        twRadioFemale->setObjectName(QString::fromUtf8("twRadioFemale"));
        twRadioFemale->setGeometry(QRect(10, 40, 99, 20));
        tabWidget->addTab(tab_2, QString());
        lblMsg = new QLabel(centralwidget);
        lblMsg->setObjectName(QString::fromUtf8("lblMsg"));
        lblMsg->setGeometry(QRect(10, 150, 351, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tbGradeGender->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tbRadioFirst->setText(QCoreApplication::translate("MainWindow", "First", nullptr));
        tbRedioSecond->setText(QCoreApplication::translate("MainWindow", "Second", nullptr));
        tbRadioThird->setText(QCoreApplication::translate("MainWindow", "Third", nullptr));
        tbGradeGender->setItemText(tbGradeGender->indexOf(page_1), QCoreApplication::translate("MainWindow", "Grade", nullptr));
        tbRadioMale->setText(QCoreApplication::translate("MainWindow", "Male", nullptr));
        tbRadioFemale->setText(QCoreApplication::translate("MainWindow", "Female", nullptr));
        tbGradeGender->setItemText(tbGradeGender->indexOf(page_2), QCoreApplication::translate("MainWindow", "Gender", nullptr));
        twRadioFirst->setText(QCoreApplication::translate("MainWindow", "First", nullptr));
        twRadioSecond->setText(QCoreApplication::translate("MainWindow", "Second", nullptr));
        twRadioThird->setText(QCoreApplication::translate("MainWindow", "Third", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Grade", nullptr));
        twRadioMale->setText(QCoreApplication::translate("MainWindow", "Male", nullptr));
        twRadioFemale->setText(QCoreApplication::translate("MainWindow", "Female", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Gender", nullptr));
        lblMsg->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
