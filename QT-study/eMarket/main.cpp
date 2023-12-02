#include "emarket.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createMySqlConn()) return 0;
    eMarket w;

    QSqlDatabase::database().close();
    w.show();
    return a.exec();

//    LoginDialog logindlg;
//    if (logindlg.exec() == QDialog::Accepted)
//    {
//        QSqlDatabase::database().close();
//        w.show();
//        return a.exec();
//    }
//    else
//    {
//        return 0;
//    }
}
