#include "emarket.h"
#include "ui_emarket.h"

eMarket::eMarket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::eMarket)
{
    ui->setupUi(this);
}

eMarket::~eMarket()
{
    delete ui;
}
