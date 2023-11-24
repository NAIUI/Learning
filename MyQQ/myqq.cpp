#include "myqq.h"
#include "ui_myqq.h"

MyQQ::MyQQ(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyQQ)
{
    ui->setupUi(this);
}

MyQQ::~MyQQ()
{
    delete ui;
}

