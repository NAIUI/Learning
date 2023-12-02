#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFontDatabase>
#include "mychildwnd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyWord; }
QT_END_NAMESPACE

class MyChildWnd;

class QMdiSubWindow;

class QSignalMapper;

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();
    void initMainWindow();      // 初始化
    void docNew();              // 新建文档

private slots:
    void on_aboutAction_triggered();

    void on_aboutQtAction_triggered();

    void on_newAction_triggered();

    void refreshMenus();                // 刷新菜单的槽函数

    void addSubWndListMenu();           // 往“窗口”主菜单下添加子窗口菜单项列表

private:
    Ui::MyWord *ui;
    void formatEnabled();
    MyChildWnd *activateChildWnd();         // 活动文档子窗口
    QSignalMapper *myWndMapper;             // 子窗口信号映射器
};

#endif // MYWORD_H
