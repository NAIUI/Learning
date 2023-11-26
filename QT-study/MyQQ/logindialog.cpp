#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setFocus();        // 设置焦点为密码框
    ui->userLineEdit->setText("小明");
    ui->pwdLineEdit->setText("123456");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginPushButton_clicked()
{
    showWeiChatWindow();                // 用于验证显示聊天窗口的方法
}

void LoginDialog::showWeiChatWindow()
{
    QString uname1("小明");  QString uname2("小红");  QString pword("123456");
    if ((uname1 != ui->userLineEdit->text() && uname2 != ui->userLineEdit->text()) || pword != ui->pwdLineEdit->text())
    {
        QMessageBox::warning(this,QObject::tr("提示"), "用户名或密码错误！");
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        return;
    }
    else
    {
        myQQ = new MyQQ(0);
        myQQ->setWindowTitle(ui->userLineEdit->text());
        myQQ->show();
    }
}
