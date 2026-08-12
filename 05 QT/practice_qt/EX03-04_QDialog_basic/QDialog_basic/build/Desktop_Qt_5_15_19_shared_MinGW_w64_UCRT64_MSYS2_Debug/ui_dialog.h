/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.19
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *btnAccept;
    QPushButton *btnReject;
    QPushButton *btnDone;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(454, 320);
        btnAccept = new QPushButton(Dialog);
        btnAccept->setObjectName(QString::fromUtf8("btnAccept"));
        btnAccept->setGeometry(QRect(30, 140, 75, 24));
        btnReject = new QPushButton(Dialog);
        btnReject->setObjectName(QString::fromUtf8("btnReject"));
        btnReject->setGeometry(QRect(180, 140, 75, 24));
        btnDone = new QPushButton(Dialog);
        btnDone->setObjectName(QString::fromUtf8("btnDone"));
        btnDone->setGeometry(QRect(330, 140, 75, 24));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        btnAccept->setText(QCoreApplication::translate("Dialog", "accept()", nullptr));
        btnReject->setText(QCoreApplication::translate("Dialog", "reject()", nullptr));
        btnDone->setText(QCoreApplication::translate("Dialog", "done()", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
