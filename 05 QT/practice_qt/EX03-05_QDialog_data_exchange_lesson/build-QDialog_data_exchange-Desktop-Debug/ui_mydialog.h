/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lblName;
    QGroupBox *groupBox_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkFishing;
    QCheckBox *chkSurfing;
    QCheckBox *chkTraveling;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName(QString::fromUtf8("MyDialog"));
        MyDialog->resize(375, 232);
        MyDialog->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	border: 2px solid rgb(182,182,182);\n"
"	margin-top: 1ex;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 5px;\n"
"	left: 10px;\n"
"}"));
        widget = new QWidget(MyDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 321, 201));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblName = new QLabel(widget);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        verticalLayout->addWidget(lblName);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        widget1 = new QWidget(groupBox_2);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(21, 30, 281, 22));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        chkFishing = new QCheckBox(widget1);
        chkFishing->setObjectName(QString::fromUtf8("chkFishing"));

        horizontalLayout_2->addWidget(chkFishing);

        chkSurfing = new QCheckBox(widget1);
        chkSurfing->setObjectName(QString::fromUtf8("chkSurfing"));

        horizontalLayout_2->addWidget(chkSurfing);

        chkTraveling = new QCheckBox(widget1);
        chkTraveling->setObjectName(QString::fromUtf8("chkTraveling"));

        horizontalLayout_2->addWidget(chkTraveling);


        verticalLayout->addWidget(groupBox_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnOK = new QPushButton(widget);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        horizontalLayout_3->addWidget(btnOK);

        btnCancel = new QPushButton(widget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout_3->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QCoreApplication::translate("MyDialog", "Dialog", nullptr));
        lblName->setText(QCoreApplication::translate("MyDialog", "Name: unknown", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MyDialog", "Hobby", nullptr));
        chkFishing->setText(QCoreApplication::translate("MyDialog", "Fishing", nullptr));
        chkSurfing->setText(QCoreApplication::translate("MyDialog", "Surfing", nullptr));
        chkTraveling->setText(QCoreApplication::translate("MyDialog", "Traveling", nullptr));
        btnOK->setText(QCoreApplication::translate("MyDialog", "OK", nullptr));
        btnCancel->setText(QCoreApplication::translate("MyDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
