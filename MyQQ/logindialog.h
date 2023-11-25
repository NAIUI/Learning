#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "myqq.h"
#include <QFile>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent= 0);
    ~LoginDialog();

private slots:
    void on_loginPushButton_clicked () ;        // "登录"按钮的单击事件方法
    void showWeiChatWindow () ;                 // 根据验证的结果决定是否显示聊天窗口

private:
    Ui::LoginDialog *ui;
    MyQQ *myQQ;                                 // 指向聊天窗口的指针
};

#endif // LOGINDIALOG_H
