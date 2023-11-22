#include "emarket.h"
#include "logindialog.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QMYSQL3");
    sqldb.setHostName("127.0.0.1");
    sqldb.setPort(3306);
    sqldb.setDatabaseName("emarket");
    sqldb.setUserName("root");
    sqldb.setPassword("root");
    if (!sqldb.open())
    {
        QMessageBox::critical(0,QObject::tr("后台数据库连接失败"), "请检查后继续！！！",
                              QMessageBox::Cancel);
        return 0;
    }
    //if (!createMySqlConn()) return 0;
    eMarket w;
    LoginDialog logindlg;
    if (logindlg.exec() == QDialog::Accepted)
    {
        QSqlDatabase::database().close();
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
