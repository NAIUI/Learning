#ifndef MYQQ_H
#define MYQQ_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyQQ; }
QT_END_NAMESPACE

class MyQQ : public QWidget
{
    Q_OBJECT

public:
    MyQQ(QWidget *parent = nullptr);
    ~MyQQ();

private:
    Ui::MyQQ *ui;
};
#endif // MYQQ_H
