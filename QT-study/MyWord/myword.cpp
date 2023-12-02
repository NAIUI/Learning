#include "myword.h"
#include "ui_myword.h"

MyWord::MyWord(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWord)
{
    ui->setupUi(this);
    initMainWindow();
}

MyWord::~MyWord()
{
    delete ui;
}


void MyWord::on_aboutAction_triggered()
{
    QMessageBox::about(this, tr("关于"), tr("这是一个基于 Qt5 实现的字处理软件\r\n"
                                          "具备类似微软 Office Word 的功能。"));
}

void MyWord::on_aboutQtAction_triggered()
{
    QMessageBox::aboutQt(this, "关于 Qt 5");
}

void MyWord::initMainWindow()
{
    QFontDatabase fontdb;

    // 设置字体
    foreach (const QString &family, fontdb.families()) ui->fronComboBox->addItem(family);
    QString defaultFontFamily = QApplication::font().family();
    ui->fronComboBox->setCurrentText(defaultFontFamily);

    // 设置大小
    foreach(int fontsize, fontdb.standardSizes()) ui->sizeComboBox->addItem(QString::number(fontsize));
    ui->sizeComboBox->setCurrentIndex(ui->sizeComboBox->findText(QString::number(QApplication::font().pointSize())));

    // 设置滚动条
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    refreshMenus();

    // 当有活动文档子窗口时刷新菜单
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(refreshMenus()));

    // 添加子窗口菜单项列表
    myWndMapper = new QSignalMapper(this);             // 创建信号映射器
    connect(myWndMapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
    addSubWndListMenu();
    // connect(ui->memW, SIGNAL (aboutTo.Show ()), this, SLOT (addSubWndListMenu ()));
}

void MyWord::docNew()
{
    MyChildWnd *childWnd = new MyChildWnd;                  // 创建 MyChildWnd 部件
    // 向多文档区域添加子窗口， childWnd 为中心部件
    ui->mdiArea->addSubWindow(childWnd);

    // 根据 QTextEdit 类是否可以复制信号，设置剪切、复制动作是否可用
    connect (childWnd, SIGNAL (copyAvailable (bool)), ui->cutAction, SLOT(setEnabled (bool)));
    connect(childWnd,SIGNAL(copyAvailable(bool)), ui->copyAction, SLOT(setEnabled(bool)));
    childWnd->newDoc();
    childWnd->show();

    // 使“格式”主菜单下各菜单项及其对应的工具按钮变为可用
    formatEnabled();
}

void MyWord::formatEnabled()
{
    ui->boldAction->setEnabled(true);
    ui->italicAction->setEnabled(true);
    ui->underlineAction->setEnabled(true);
    ui->leftAlignAction->setEnabled(true);
    ui->centerAction->setEnabled(true);
    ui->rightAlignAction->setEnabled(true);
    ui->justifyAction->setEnabled(true);
    ui->colorAction->setEnabled(true);
}

void MyWord::on_newAction_triggered()
{
    docNew();
}

void MyWord::refreshMenus()
{
    // 至少有一个文档子窗口打开的情况
    bool hasChild = (activateChildWnd() != 0);
    ui->saveAction->setEnabled(hasChild);
    ui->saveAsAction->setEnabled(hasChild);
    ui->printAction->setEnabled(hasChild);
    ui->printPreviewAction->setEnabled(hasChild);
    ui->pasteAction->setEnabled(hasChild);
    ui->closeAction->setEnabled(hasChild);
    ui->closeAllAction->setEnabled(hasChild);
    ui->tiledeAction->setEnabled(hasChild);
    ui->cascadeaction->setEnabled(hasChild);
    ui->nextAction->setEnabled(hasChild);
    ui->previousAction->setEnabled(hasChild);
    // 文档己打开并且其中有内容被选中的情况
    bool hasSelect = (activateChildWnd () && activateChildWnd()->textCursor().hasSelection());
    ui->cutAction->setEnabled(hasSelect);
    ui->copyAction->setEnabled(hasSelect);
    ui->boldAction->setEnabled(hasSelect);
    ui->italicAction->setEnabled(hasSelect);
    ui->underlineAction->setEnabled(hasSelect);
    ui->leftAlignAction->setEnabled(hasSelect);
    ui->centerAction->setEnabled(hasSelect);
    ui->rightAlignAction->setEnabled(hasSelect);
    ui->justifyAction->setEnabled(hasSelect);
    ui->colorAction->setEnabled(hasSelect);
}

MyChildWnd *MyWord::activateChildWnd()
{
    // 若有活动文档窗口则将其内的中心部件转换为 MyChildWnd 类型；若没有则直接返回
    if (QMdiSubWindow *actSubWnd = ui->mdiArea->activeSubWindow())
        return qobject_cast<MyChildWnd *>(actSubWnd->widget());
    else
        return 0;
}
