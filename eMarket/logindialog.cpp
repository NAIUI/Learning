#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QSqlError>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setFixedSize(400,300);          // 固定登录对话框大小
    setWindowTitle(tr("登录"));
    ui->pwdLineEdit->setFocus();    // 口令框焦点
}

LoginDialog::~LoginDialog()
{
    delete ui;
}



void LoginDialog::on_loginPushButton_clicked()
{
    if (!ui->pwdLineEdit->text().isEmpty())
    {
        if(ui->pwdLineEdit->text().isEmpty()){
            QMessageBox::information(this,tr("请输入密码"),tr("请先输入密码再登录！"),QMessageBox::Ok);
            ui->pwdLineEdit->setFocus();
        }else{
            QSqlQuery query;
            if (!query.exec("SELECT PassWord FROM member")) qDebug() << query.lastError().text();;
            query.next() ;
            if(query.value(0).toString() == ui->pwdLineEdit->text()){
                QDialog::accept();
            }else{
                QMessageBox::warning(this,tr("密码错误"),tr("请输入正确的密码再登录！"),QMessageBox::Ok);
                ui->pwdLineEdit->clear();
                ui->pwdLineEdit->setFocus();
            }
        }
    }
}

//QString LoginDialog::strToMD5(QString str)
//{
//    QString strMD5;
//    QByteArray qba;
//    qba = QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5);
//    strMD5.append(qba.toHex());
//    return strMD5;
//}

void LoginDialog::on_exitPushButton_clicked()
{
        QDialog::reject();
}
