#include "mychildwnd.h"

MyChildWnd::MyChildWnd()
{
    setAttribute(Qt::WA_DeleteOnClose);         // 子窗口关闭时销毁该类的对象实例
    beSaved = false;                            // 初始文档尚未保存
}

void MyChildWnd::newDoc()
{
    // 设置窗口编号
    static int wndSeqNum = 1;

    // 将当前打开的文档命名为"Word 文档 编号"的形式，编号在使用一次后自增1
    myCurDocPath = tr("Word 文档 %1").arg(wndSeqNum++);

    // 设置窗口标题，文档被改动后在其名称后显示“*”号标识
    setWindowTitle(myCurDocPath + "[*]" + tr(" - MyWord"));

    //文档被改动时发送contentChanged() 信号，执行自定义docBeModify()槽函数
    connect(this, SIGNAL(contentChanged()),this,SLOT(docBeModified()));
}

void MyChildWnd::docBeModified()
{
    setWindowModified(document()->isModified());        // 判断文档内容是否被修改
}

QString MyChildWnd::getCurDocName()
{
    return QFileInfo(myCurDocPath).fileName();
}
