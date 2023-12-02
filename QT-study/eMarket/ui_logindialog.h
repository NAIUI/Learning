/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *adminLineEdit;
    QLineEdit *pwdLineEdit;
    QPushButton *loginPushButton;
    QPushButton *exitPushButton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(366, 253);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 25, 251, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 100, 61, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 150, 51, 20));
        label_3->setFont(font1);
        adminLineEdit = new QLineEdit(LoginDialog);
        adminLineEdit->setObjectName(QString::fromUtf8("adminLineEdit"));
        adminLineEdit->setGeometry(QRect(160, 100, 113, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(14);
        adminLineEdit->setFont(font2);
        pwdLineEdit = new QLineEdit(LoginDialog);
        pwdLineEdit->setObjectName(QString::fromUtf8("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(160, 150, 113, 20));
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        loginPushButton = new QPushButton(LoginDialog);
        loginPushButton->setObjectName(QString::fromUtf8("loginPushButton"));
        loginPushButton->setGeometry(QRect(100, 190, 71, 31));
        loginPushButton->setFont(font1);
        exitPushButton = new QPushButton(LoginDialog);
        exitPushButton->setObjectName(QString::fromUtf8("exitPushButton"));
        exitPushButton->setGeometry(QRect(200, 190, 71, 31));
        exitPushButton->setFont(font1);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\346\254\242 \350\277\216 \350\277\233 \345\205\245 \347\224\265 \345\255\220 \345\225\206 \345\237\216", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\347\256\241 \347\220\206 \345\221\230", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", " \345\217\243 \344\273\244", nullptr));
        adminLineEdit->setText(QCoreApplication::translate("LoginDialog", "b02020622", nullptr));
        loginPushButton->setText(QCoreApplication::translate("LoginDialog", "\347\231\273 \345\275\225", nullptr));
        exitPushButton->setText(QCoreApplication::translate("LoginDialog", "\351\200\200 \345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
