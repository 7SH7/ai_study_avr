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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
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
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *lblActivate;
    QComboBox *cboActivate;
    QLabel *lblHighlight;
    QComboBox *cboHighlight;
    QLabel *lblEditableFalse;
    QComboBox *cboEditableFalse;
    QLabel *lblEditableTrue;
    QComboBox *cboEditableTrue;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(260, 166);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 221, 108));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lblActivate = new QLabel(formLayoutWidget);
        lblActivate->setObjectName(QString::fromUtf8("lblActivate"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblActivate);

        cboActivate = new QComboBox(formLayoutWidget);
        cboActivate->addItem(QString());
        cboActivate->addItem(QString());
        cboActivate->addItem(QString());
        cboActivate->addItem(QString());
        cboActivate->setObjectName(QString::fromUtf8("cboActivate"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cboActivate);

        lblHighlight = new QLabel(formLayoutWidget);
        lblHighlight->setObjectName(QString::fromUtf8("lblHighlight"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblHighlight);

        cboHighlight = new QComboBox(formLayoutWidget);
        cboHighlight->addItem(QString());
        cboHighlight->addItem(QString());
        cboHighlight->addItem(QString());
        cboHighlight->addItem(QString());
        cboHighlight->setObjectName(QString::fromUtf8("cboHighlight"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cboHighlight);

        lblEditableFalse = new QLabel(formLayoutWidget);
        lblEditableFalse->setObjectName(QString::fromUtf8("lblEditableFalse"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblEditableFalse);

        cboEditableFalse = new QComboBox(formLayoutWidget);
        cboEditableFalse->addItem(QString());
        cboEditableFalse->addItem(QString());
        cboEditableFalse->addItem(QString());
        cboEditableFalse->addItem(QString());
        cboEditableFalse->setObjectName(QString::fromUtf8("cboEditableFalse"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cboEditableFalse);

        lblEditableTrue = new QLabel(formLayoutWidget);
        lblEditableTrue->setObjectName(QString::fromUtf8("lblEditableTrue"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblEditableTrue);

        cboEditableTrue = new QComboBox(formLayoutWidget);
        cboEditableTrue->addItem(QString());
        cboEditableTrue->addItem(QString());
        cboEditableTrue->addItem(QString());
        cboEditableTrue->addItem(QString());
        cboEditableTrue->setObjectName(QString::fromUtf8("cboEditableTrue"));
        cboEditableTrue->setEditable(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, cboEditableTrue);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 260, 19));
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
        lblActivate->setText(QCoreApplication::translate("MainWindow", "activate", nullptr));
        cboActivate->setItemText(0, QCoreApplication::translate("MainWindow", "item0", nullptr));
        cboActivate->setItemText(1, QCoreApplication::translate("MainWindow", "item1", nullptr));
        cboActivate->setItemText(2, QCoreApplication::translate("MainWindow", "item2", nullptr));
        cboActivate->setItemText(3, QCoreApplication::translate("MainWindow", "item3", nullptr));

        lblHighlight->setText(QCoreApplication::translate("MainWindow", "highlight", nullptr));
        cboHighlight->setItemText(0, QCoreApplication::translate("MainWindow", "item0", nullptr));
        cboHighlight->setItemText(1, QCoreApplication::translate("MainWindow", "item1", nullptr));
        cboHighlight->setItemText(2, QCoreApplication::translate("MainWindow", "item2", nullptr));
        cboHighlight->setItemText(3, QCoreApplication::translate("MainWindow", "item3", nullptr));

        lblEditableFalse->setText(QCoreApplication::translate("MainWindow", "Editable:False", nullptr));
        cboEditableFalse->setItemText(0, QCoreApplication::translate("MainWindow", "item0", nullptr));
        cboEditableFalse->setItemText(1, QCoreApplication::translate("MainWindow", "item1", nullptr));
        cboEditableFalse->setItemText(2, QCoreApplication::translate("MainWindow", "item2", nullptr));
        cboEditableFalse->setItemText(3, QCoreApplication::translate("MainWindow", "item3", nullptr));

        lblEditableTrue->setText(QCoreApplication::translate("MainWindow", "Editable:True", nullptr));
        cboEditableTrue->setItemText(0, QCoreApplication::translate("MainWindow", "item0", nullptr));
        cboEditableTrue->setItemText(1, QCoreApplication::translate("MainWindow", "item1", nullptr));
        cboEditableTrue->setItemText(2, QCoreApplication::translate("MainWindow", "item2", nullptr));
        cboEditableTrue->setItemText(3, QCoreApplication::translate("MainWindow", "item3", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
