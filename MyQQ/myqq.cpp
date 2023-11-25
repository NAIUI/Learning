#include "myqq.h"
#include "ui_myqq.h"

MyQQ::MyQQ(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyQQ)
{
    ui->setupUi(this);
    initMainWindow();

    // test
    ui->userListTableWidget->insertRow(0);
    ui->userListTableWidget->setItem(0, 1, new QTableWidgetItem("name"));
}

MyQQ::~MyQQ()
{
    delete ui;
}

void MyQQ::initMainWindow()
{
    myUdpSocket = new QUdpSocket(this);
    myUdpPort = 23232;
    myUdpSocket->bind(QHostAddress::Any, myUdpPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(myUdpSocket, SIGNAL(readyRead()), this, SLOT(recvAndProcessChatMsg()));
    myfsrv = new FileSrvDlg(this);
    connect(myfsrv, SIGNAL(sendFileName(QString)), this, SLOT(getSfileName(QString)));
}

void MyQQ::on_searchPushButton_clicked()
{
    myname = this->windowTitle();
    ui->userLabel->setText(myname);
    sendChatMsg(OnLine);
}

void MyQQ::sendChatMsg(ChatMsgType msgType, QString rmtName)
{
    QByteArray qba;
    QDataStream write(&qba, QIODevice::WriteOnly);
    QString locHostIp = getLocHostIp();
    QString locChatMsg = getLocChatMsg();
    write<< msgType << myname;
    switch (msgType)
    {
        case ChatMsg:
            write << locHostIp << locChatMsg;
            break;
        case OnLine:
            write << locHostIp;
            break;
        case OffLine:
            break;
        case SfileName:
            write << locHostIp << rmtName << myFileName;
            break;
    case RefFile:
            write << locHostIp << rmtName;
            break;
    }
    myUdpSocket->writeDatagram(qba, qba.length(), QHostAddress::Broadcast, myUdpPort);
}

void MyQQ::recvAndProcessChatMsg()
{
    while (myUdpSocket->hasPendingDatagrams())
    {
        QByteArray qba;
        qba.resize(myUdpSocket->pendingDatagramSize());
        myUdpSocket->readDatagram (qba.data(), qba.size());
        QDataStream read(&qba, QIODevice::ReadOnly);
        int msgType;
        read>> msgType;
        QString name, hostip, chatmsg, rname, fname;

        QString curtime = QDateTime::currentDateTime().toString ("yyyy-MM-dd hh:mm::ss");
        switch (msgType)
        {
            case ChatMsg:
                read >> name >> hostip >> chatmsg;
                ui->chatTextBrowser->setTextColor(Qt::darkGreen);
                ui->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 14));
                ui->chatTextBrowser->append("【"+name+"】"+ curtime);
                ui->chatTextBrowser->append(chatmsg);
                break;
            case OnLine:
                read>> name>> hostip;
                onLine(name, curtime);
                break;
            case OffLine:
                read>> name;
                offLine(name, curtime);
                break;
            case SfileName:
                read>> name>> hostip >> rname >> fname;
                recvFileName(name, hostip, rname, fname);
                break;
            case RefFile:
                read>> name>> hostip >> rname;
                if(myname == rname) myfsrv->cntRefused();
                break;
        }
    }
}

void MyQQ::onLine(QString name, QString time)
{
    bool notExist = ui->userListTableWidget->findItems(name, Qt::MatchExactly).isEmpty();
    if(notExist)
    {
        QTableWidgetItem *newuser = new QTableWidgetItem(name);
        ui->userListTableWidget->insertRow(0);
        ui->userListTableWidget->setItem(0, 0, newuser);
        ui->chatTextBrowser->setTextColor(Qt::gray);
        ui->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 12));
        ui->chatTextBrowser->append(tr("%1 %2 上线!").arg(time).arg(name));
        // sendChatMsg(OnLine);           // 该功能存在问题，会循环发送消息
    }
}

void MyQQ::offLine(QString name, QString time)
{
    int row = ui->userListTableWidget->findItems(name, Qt::MatchExactly).first()->row();
    ui->userListTableWidget->removeRow(row);
    ui->chatTextBrowser->setTextColor(Qt::gray);
    ui->chatTextBrowser->setCurrentFont(QFont("Times New Roman", 12));
    ui->chatTextBrowser->append(tr("%1 %2 离线! ") .arg(time) .arg(name));
}

void MyQQ::closeEvent(QCloseEvent *event)
{
    sendChatMsg(OffLine);
}

QString MyQQ::getLocHostIp()
{
    QList<QHostAddress> addrlist = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrlist)
        if(addr.protocol() == QAbstractSocket::IPv4Protocol) return addr.toString();
    return "";

}

QString MyQQ::getLocChatMsg()
{
    QString chatmsg = ui->chatTextEdit->toHtml();
    ui->chatTextEdit->clear();
    ui->chatTextEdit->setFocus();
    return chatmsg;
}

void MyQQ::on_sendPushButton_clicked()
{
    sendChatMsg(ChatMsg);
}

void MyQQ::getSfileName(QString fname)
{
    myFileName = fname;
    int row= ui->userListTableWidget->currentRow();
    QString rmtName = ui->userListTableWidget->item(row, 0)->text();
    sendChatMsg(SfileName, rmtName);
}

void MyQQ::on_transPushButton_clicked()
{
    if(ui->userListTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("选择好友"), tr(" 请先选择文件接收方! "), QMessageBox::Ok);
        return;
    }
    myfsrv->show();
}

void MyQQ::recvFileName(QString name, QString hostip, QString rmtname, QString filename)
{
    if(myname == rmtname)
    {
        int result= QMessageBox::information(this, tr(" 收到文件"), tr(" 好友号 %1 给您发文件： \r\n 2, 是否接收? ")
                                             .arg(name).arg(filename), QMessageBox::Yes, QMessageBox::No);
        if(result == QMessageBox::Yes)
        {
            QString fname = QFileDialog::getSaveFileName(0, tr ("保存"),filename);
            if (!fname. isEmpty ())
            {
                FileCntDlg *fcnt = new FileCntDlg();
                fcnt->getLocPath(fname);
                fcnt->getSrvAddr(QHostAddress(hostip));
                fcnt->show();
            }
        }
        else
        {
            sendChatMsg(RefFile, name);
        }
    }
}
