#ifndef MYQQ_H
#define MYQQ_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QUdpSocket>                           // 使用 UDP 套接口的类库
#include <QNetworkInterface>                    // 网络 (IP 地址）接口类库
#include <QDateTime>                            // 时间日期库
#include <QFile>                                // 系统文件类库
#include <QFileDialog>                          // 文件对话框库

#include "filecntdlg.h"
#include "filesrvdlg.h"

class FileSrvDlg;
class FileCntDlg;


QT_BEGIN_NAMESPACE
namespace Ui { class MyQQ; }
QT_END_NAMESPACE

enum ChatMsgType { ChatMsg, OnLine, OffLine, SfileName, RefFile }; //聊天内容,用户上线,用户离线,要传输的文件名,拒收文件

class MyQQ : public QWidget
{
    Q_OBJECT

public:
    MyQQ(QWidget *parent = nullptr);
    ~MyQQ();
    void initMainWindow();                              // 窗口初始化方法
    void onLine(QString name, QString time);            // 新用户上线方法
    void offLine(QString name, QString time);           // 用户离线方法
    void sendChatMsg(ChatMsgType msgType, QString rmtNarne = "");   // 发送 UDP 消息
    QString getLocHostIp();                             // 获取本端的 IP 地址
    QString getLocChatMsg ();                           // 获取本端的聊天信息内容
    void recvFileName(QString name, QString hostip, QString rmtname, QString filename);

protected:
    void closeEvent(QCloseEvent *event);                // 重写关闭窗口方法以便发送通知离线消息

private slots:
    void on_sendPushButton_clicked();                   // "发送”按钮的单击事件方法
    void recvAndProcessChatMsg();                       // 接收并处理 UDP 数据报
    void on_searchPushButton_clicked();                 // 搜索线上所有用户
    void getSfileName(QString);
    void on_transPushButton_clicked();

private:
    Ui::MyQQ *ui;

    QString myname = "";                                // 本端当前的用户名
    QUdpSocket *myUdpSocket;                            // 套接口指针
    qint16 myUdpPort;                                   // UDP 端口号
    QString myFileName;
    FileSrvDlg *myfsrv = new FileSrvDlg();

};

#endif // MYQQ_H
