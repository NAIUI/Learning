#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QMessageBox>

bool createMySqlConn()
{
    QSqlDatabase sqldb = QSqlDatabase::addDatabase("QMYSQL");
    sqldb.setHostName("127.0.0.1");
    sqldb.setPort(3306);
    sqldb.setDatabaseName("emarket");
    sqldb.setUserName("root");
    sqldb.setPassword("root");
    if (!sqldb.open())
    {
        QMessageBox::critical(0,QObject::tr("后台数据库连接失败"), "请检查后继续！！！",
                              QMessageBox::Cancel);
        return false;
    }

    // 检查连接是否有效
    if (sqldb.isValid()) {
        // 获取连接参数
        QString hostName = sqldb.hostName();
        QString databaseName = sqldb.databaseName();
        QString userName = sqldb.userName();
        QString password = sqldb.password();

        // 打印连接参数
        qDebug() << "Host Name: " << hostName;
        qDebug() << "Database Name: " << databaseName;
        qDebug() << "User Name: " << userName;
        qDebug() << "Password: " << password;
    } else {
        // 连接无效，可能连接失败或者没有建立连接
        qDebug() << "Invalid database connection.";
    }
    return true;
}

#endif // CONNECTION_H
