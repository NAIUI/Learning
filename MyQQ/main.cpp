#include "myqq.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog logindlg;
    logindlg.show();
    return a.exec();
}
