#include "myqq.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyQQ w;
    LoginDialog l; l.show();
    //w.show();
    return a.exec();
}
